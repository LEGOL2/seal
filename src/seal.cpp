#include <SFML/Graphics.hpp>
#include <global_state.hpp>
#include <seal/seal.hpp>
#include <stack>
#include <vector>

std::unique_ptr<sf::RenderWindow> g_window{};
uint32_t g_width{400}, g_height{400};
sf::String g_currentTitle{"seal"};

enum seal::EllipseMode g_currentEllipseMode{seal::EllipseMode::CENTER};

sf::Color g_currentBackground{200, 200, 200};
sf::Color g_currentFill{255, 255, 255};
bool g_fillEnabled{true};
sf::Color g_currentStroke{0, 0, 0};
float g_currentStrokeWeight{2};
bool g_strokeEnabled{true};

float g_mouseX{0}, g_mouseY{0};
bool g_mouseIsPressed{false};

namespace {
std::vector<uint8_t> g_pixelBuffer;
bool g_pixelsDirty{false};
sf::Texture g_canvasTexture;

// Holds information controlled by fill(), stroke(), tint(), strokeWeight(), strokeCap(), strokeJoin(), imageMode(),
// rectMode(), ellipseMode(), shapeMode(), colorMode(), textAlign(), textFont(), textMode(), textSize(), textLeading(),
// emissive(), specular(), shininess(), ambient()
struct StyleState {
    sf::Color fill, stroke;
    float strokeWeight;
    bool fillEnabled, strokeEnabled;
};
std::stack<StyleState> g_styleStack;

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
            g_mouseX = static_cast<float>(mouseMoved->position.x);
            g_mouseY = static_cast<float>(mouseMoved->position.y);
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

constexpr seal::Color::Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha)
    : r(red), g(green), b(blue), a(alpha) {}

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

seal::Color seal::getPixel(uint32_t x, uint32_t y) {
    const size_t index = (y * g_window->getSize().x + x) * 4;
    return seal::Color{g_pixelBuffer[index], g_pixelBuffer[index + 1], g_pixelBuffer[index + 2],
                       g_pixelBuffer[index + 3]};
}

void seal::loadPixels() {
    auto windwSize = g_window->getSize();
    g_pixelBuffer.resize(windwSize.x * windwSize.y * 4);
    if (!g_canvasTexture.resize(windwSize)) {
        std::abort();
    }
    g_canvasTexture.update(*g_window);
    auto img = g_canvasTexture.copyToImage();
    auto* srcPixels = img.getPixelsPtr();
    std::memcpy(g_pixelBuffer.data(), srcPixels, g_pixelBuffer.size());
}

void seal::setPixel(uint32_t x, uint32_t y, const Color& color) {
    const size_t index = (y * g_window->getSize().x + x) * 4;
    g_pixelBuffer[index] = color.r;
    g_pixelBuffer[index + 1] = color.g;
    g_pixelBuffer[index + 2] = color.b;
    g_pixelBuffer[index + 3] = color.a;
    g_pixelsDirty = true;
}

void seal::updatePixels() {
    if (!g_pixelsDirty) {
        return;
    }

    sf::Image img(g_window->getSize(), g_pixelBuffer.data());
    g_canvasTexture.update(img);

    sf::Sprite sprite(g_canvasTexture);
    g_window->draw(sprite);
    g_pixelsDirty = false;
}

void seal::background(uint8_t gray, uint8_t alpha) { g_currentBackground = {gray, gray, gray, alpha}; }
void seal::background(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
    g_currentBackground = {red, green, blue, alpha};
}

void seal::fill(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
    g_fillEnabled = true;
    g_currentFill = {red, green, blue, alpha};
}

void seal::fill(uint8_t gray, uint8_t alpha) {
    g_fillEnabled = true;
    g_currentFill = {gray, gray, gray, alpha};
}

void seal::noFill() { g_fillEnabled = false; }

void seal::noStroke() { g_strokeEnabled = false; }

void seal::stroke(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
    g_strokeEnabled = true;
    g_currentStroke = {red, green, blue, alpha};
}

void seal::popStyle() {
    if (g_styleStack.empty()) {
        return;
    }

    const auto& style = g_styleStack.top();
    g_currentFill = style.fill;
    g_currentStroke = style.stroke;
    g_currentStrokeWeight = style.strokeWeight;
    g_fillEnabled = style.fillEnabled;
    g_strokeEnabled = style.strokeEnabled;

    g_styleStack.pop();
}

void seal::pushStyle() {
    g_styleStack.push({g_currentFill, g_currentStroke, g_currentStrokeWeight, g_fillEnabled, g_strokeEnabled});
}

uint32_t seal::height() { return g_height; }

void seal::size(uint32_t w, uint32_t h) {
    g_width = w;
    g_height = h;
    g_window->setSize({g_width, g_height});
    sf::View view(sf::FloatRect({0, 0}, {static_cast<float>(g_width), static_cast<float>(g_height)}));
    g_window->setView(view);
}

uint32_t seal::width() { return g_width; }

void seal::windowTitle(const char* title) {
    g_currentTitle = title;
    g_window->setTitle(g_currentTitle);
}
