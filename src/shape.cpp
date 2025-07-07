#include <SFML/Graphics.hpp>
#include <global_state.hpp>
#include <seal.hpp>
#include <shapes/ellipse.hpp>

static void set_position_fill_stroke(sf::Shape &shape, sf::Vector2f position) {
    shape.setPosition(position);
    shape.setFillColor(g_currentFill);

    if (g_strokeEnabled) {
        shape.setOutlineThickness(g_currentStrokeWeight);
        shape.setOutlineColor(g_currentStroke);
    }
}

void seal::circle(float x, float y, float radius) {
    sf::CircleShape shape(radius);
    set_position_fill_stroke(shape, {x - radius, y - radius});
    g_window->draw(shape);
}

void seal::ellipse(float x, float y, float width, float height) {
    EllipseShape shape({width, height});
    set_position_fill_stroke(shape, {x - width, y - height});
    g_window->draw(shape);
}

void seal::line(float x1, float y1, float x2, float y2) {
    const sf::Vector2f vec = {x2 - x1, y2 - y1};
    const sf::Angle angle = sf::radians(std::atan2f(vec.y, vec.x));
    sf::RectangleShape shape({vec.length(), g_currentStrokeWeight});
    shape.setPosition({x1, y1});
    shape.rotate(angle);
    shape.setFillColor(g_currentStroke);
    g_window->draw(shape);
}

void seal::rect(float x, float y, float w, float h) {
    sf::RectangleShape shape({w, h});
    set_position_fill_stroke(shape, {x, y});
    g_window->draw(shape);
}

void seal::strokeWeight(float weight) {
    g_currentStrokeWeight = weight;
}
