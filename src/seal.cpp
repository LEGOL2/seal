#include <SFML/Graphics.hpp>
#include <global_state.hpp>
#include <seal.hpp>

std::unique_ptr<sf::RenderWindow> g_window{};
uint32_t g_width{400}, g_height{400};
sf::String g_currentTitle{"seal"};

sf::Color g_currentBackground{200, 200, 200};
sf::Color g_currentFill{255, 255, 255};
bool g_fillEnabled{true};
sf::Color g_currentStroke{0, 0, 0};
float g_currentStrokeWeight{2};
bool g_strokeEnabled{true};

float g_mouseX{0}, g_mouseY{0};
bool g_mouseIsPressed{false};

namespace {
void handleEvents() {
    while (const std::optional event = g_window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            g_window->close();
            break;
        }

        if (const auto* keyPress = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPress->code == sf::Keyboard::Key::Escape) {
                g_window->close();
            }
        } else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
            g_mouseX = mouseMoved->position.x;
            g_mouseY = mouseMoved->position.y;
        } else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            g_mouseIsPressed = true;
        } else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonReleased>()) {
            g_mouseIsPressed = false;
        }
    }
}

void beginFrame() { g_window->clear(g_currentBackground); }

void endFrame() { g_window->display(); }

}  // namespace

void seal::init() {
    static bool initialized = false;
    if (!initialized) {
        sf::ContextSettings settings;
        settings.antiAliasingLevel = 8;
        g_window = std::make_unique<sf::RenderWindow>(sf::VideoMode({g_width, g_height}), g_currentTitle,
                                                      sf::Style::Close, sf::State::Windowed, settings);
        sf::View view(sf::FloatRect({0, 0}, {static_cast<float>(g_width), static_cast<float>(g_height)}));
        g_window->setView(view);
        g_window->setFramerateLimit(60);
        initialized = true;
    }
}

void seal::run() {
    if (!g_window) {
        init();
    }
    setup();

    while (g_window->isOpen()) {
        handleEvents();
        beginFrame();
        draw();
        endFrame();
    }
}

void seal::background(uint8_t gray) { g_currentBackground = {gray, gray, gray}; }
void seal::background(uint8_t red, uint8_t green, uint8_t blue) { g_currentBackground = {red, green, blue}; }

void seal::fill(uint8_t gray) {
    g_fillEnabled = true;
    g_currentFill = {gray, gray, gray};
}

void seal::fill(uint8_t red, uint8_t green, uint8_t blue) {
    g_fillEnabled = true;
    g_currentFill = {red, green, blue};
}

void seal::noFill() { g_fillEnabled = false; }

void seal::noStroke() { g_strokeEnabled = false; }

void seal::stroke(uint8_t red, uint8_t green, uint8_t blue) {
    g_strokeEnabled = true;
    g_currentStroke = {red, green, blue};
}

void seal::size(uint32_t w, uint32_t h) {
    g_width = w;
    g_height = h;
    g_window->setSize({g_width, g_height});
    sf::View view(sf::FloatRect({0, 0}, {static_cast<float>(g_width), static_cast<float>(g_height)}));
    g_window->setView(view);
}

void seal::windowTitle(const char* title) {
    g_currentTitle = title;
    g_window->setTitle(g_currentTitle);
}
