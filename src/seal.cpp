#include <SFML/Graphics.hpp>
#include <memory>
#include <seal.hpp>
#include <util.hpp>

namespace {
// Global state
std::unique_ptr<sf::RenderWindow> window{};
uint32_t width{400}, height{400};
sf::String currentTitle{"seal"};

sf::Color currentBackground{0, 0, 0};
sf::Color currentFill{255, 255, 255};
sf::Color currentStroke{0, 0, 0};
float currentStrokeWeight{1};
bool strokeEnabled{true};

float mouseX{0}, mouseY{0};
bool mouseIsPressed{false};

void handleEvents() {
    while (const std::optional event = window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window->close();
            break;
        }

        if (const auto* keyPress = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPress->code == sf::Keyboard::Key::Escape) {
                window->close();
            }
        } else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
            mouseX = mouseMoved->position.x;
            mouseY = mouseMoved->position.y;
        } else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            mouseIsPressed = true;
        } else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonReleased>()) {
            mouseIsPressed = false;
        }
    }
}

void beginFrame() { window->clear(currentBackground); }

void endFrame() { window->display(); }

}  // namespace

void seal::init() {
    static bool initialized = false;
    if (!initialized) {
        window = std::make_unique<sf::RenderWindow>(sf::VideoMode({width, height}), currentTitle);
        window->setFramerateLimit(60);
        initialized = true;
    }
}

void seal::run() {
    if (!window) {
        init();
    }
    setup();

    while (window->isOpen()) {
        handleEvents();
        beginFrame();
        draw();
        endFrame();
    }
}

void seal::background(uint8_t gray) { currentBackground = {gray, gray, gray}; }
void seal::background(uint8_t red, uint8_t green, uint8_t blue) { currentBackground = {red, green, blue}; }

void seal::fill(uint8_t gray) { currentFill = {gray, gray, gray}; }

void seal::fill(uint8_t red, uint8_t green, uint8_t blue) { currentFill = {red, green, blue}; }

void seal::rect(float x, float y, float w, float h) {
    sf::RectangleShape shape({w, h});
    shape.setPosition({x, y});
    shape.setFillColor(currentFill);

    if (strokeEnabled) {
        shape.setOutlineThickness(currentStrokeWeight);
        shape.setOutlineColor(currentStroke);
    }

    window->draw(shape);
}

void seal::size(uint32_t w, uint32_t h) {
    width = w;
    height = h;
    window->setSize({width, height});
}

void seal::title(const char* title) {
    currentTitle = title;
    window->setTitle(currentTitle);
}
