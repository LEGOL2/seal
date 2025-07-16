#include <SFML/Graphics.hpp>
#include <global_state.hpp>
#include <helper.hpp>
#include <seal.hpp>
#include <shapes/ellipse.hpp>

static void set_position_fill_stroke(sf::Shape &shape, sf::Vector2f position) {
    shape.setPosition(position);

    if (g_fillEnabled) {
        shape.setFillColor(g_currentFill);
    } else {
        shape.setFillColor(sf::Color::Transparent);
    }

    if (g_strokeEnabled) {
        shape.setOutlineThickness(g_currentStrokeWeight);
        shape.setOutlineColor(g_currentStroke);
    }
}

void seal::circle(float x, float y, float radius) {
    sf::CircleShape shape(radius);

    if (g_strokeEnabled) {
        const float halfStroke = g_currentStrokeWeight / 2.f;
        shape.setRadius(radius - halfStroke);
    }

    set_position_fill_stroke(shape, {x - radius, y - radius});
    g_window->draw(shape);
}

void seal::ellipse(float a, float b, float c, float d) {
    float r1, r2;
    switch (g_currentEllipseMode) {
        case CENTER:
            r1 = c / 2.f;
            r2 = d / 2.f;
            break;
        case RADIUS:
            r1 = c;
            r2 = d;
            break;
        case CORNER:
            break;
        case CORNERS:
            break;
        default:
            return;
    }

    if (g_strokeEnabled) {
        const float halfStroke = g_currentStrokeWeight / 2.f;
        r1 -= halfStroke;
        r2 -= halfStroke;
    }

    EllipseShape shape({r1, r2});
    set_position_fill_stroke(shape, {a - r1, b - r2});
    g_window->draw(shape);
}

void seal::line(float x1, float y1, float x2, float y2) {
    if (g_currentStrokeWeight <= 2) {  // Use primitive line
        sf::VertexArray line(sf::PrimitiveType::Lines, 2);
        line[0] = sf::Vertex{sf::Vector2f(x1, y1), g_currentStroke};
        line[1] = sf::Vertex{sf::Vector2f(x2, y2), g_currentStroke};
        g_window->draw(line);
    } else {  // Use rotated rectangle
        const sf::Vector2f vec = {x2 - x1, y2 - y1};
        sf::RectangleShape shape({std::hypot(vec.x, vec.y), g_currentStrokeWeight});
        shape.setPosition({x1, y1});
        shape.setOrigin({0, g_currentStrokeWeight / 2.f});
        shape.setRotation(sf::radians(std::atan2f(vec.y, vec.x)));
        shape.setFillColor(g_currentStroke);
        g_window->draw(shape);
    }
}

void seal::point(float x, float y) {
    const sf::Vertex vertex{sf::Vector2f(x, y), g_currentStroke};
    g_window->draw(&vertex, 1, sf::PrimitiveType::Points);
}

void seal::quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    sf::ConvexShape shape(4);

    if (g_strokeEnabled) {
        const float halfStroke = g_currentStrokeWeight / 2.f;
        const float centroidX = (x1 + x2 + x3 + x4) / 4.0f;
        const float centroidY = (y1 + y2 + y3 + y4) / 4.0f;
        shape.setPoint(0, {x1 + (centroidX - x1) * (halfStroke / distance(x1, y1, centroidX, centroidY)),
                           y1 + (centroidY - y1) * (halfStroke / distance(x1, y1, centroidX, centroidY))});
        shape.setPoint(1, {x2 + (centroidX - x2) * (halfStroke / distance(x2, y2, centroidX, centroidY)),
                           y2 + (centroidY - y2) * (halfStroke / distance(x2, y2, centroidX, centroidY))});
        shape.setPoint(2, {x3 + (centroidX - x3) * (halfStroke / distance(x3, y3, centroidX, centroidY)),
                           y3 + (centroidY - y3) * (halfStroke / distance(x3, y3, centroidX, centroidY))});
        shape.setPoint(3, {x4 + (centroidX - x4) * (halfStroke / distance(x4, y4, centroidX, centroidY)),
                           y4 + (centroidY - y4) * (halfStroke / distance(x4, y4, centroidX, centroidY))});
    } else {
        shape.setPoint(0, {x1, y1});
        shape.setPoint(1, {x2, y2});
        shape.setPoint(2, {x3, y3});
        shape.setPoint(3, {x4, y4});
    }

    set_position_fill_stroke(shape, {0, 0});
    g_window->draw(shape);
}

void seal::rect(float x, float y, float w, float h) {
    sf::RectangleShape shape({w, h});

    if (g_strokeEnabled) {
        const float halfStroke = g_currentStrokeWeight / 2.f;
        shape.setSize({w - g_currentStrokeWeight, h - g_currentStrokeWeight});
        x += halfStroke;
        y += halfStroke;
    }

    set_position_fill_stroke(shape, {x, y});
    g_window->draw(shape);
}

void seal::square(float x, float y, float extent) { rect(x, y, extent, extent); }

void seal::triangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    sf::ConvexShape shape(3);

    if (g_strokeEnabled) {
        const float halfStroke = g_currentStrokeWeight / 2.f;
        const float centroidX = (x1 + x2 + x3) / 3.0f;
        const float centroidY = (y1 + y2 + y3) / 3.0f;
        shape.setPoint(0, {x1 + (centroidX - x1) * (halfStroke / distance(x1, y1, centroidX, centroidY)),
                           y1 + (centroidY - y1) * (halfStroke / distance(x1, y1, centroidX, centroidY))});
        shape.setPoint(1, {x2 + (centroidX - x2) * (halfStroke / distance(x2, y2, centroidX, centroidY)),
                           y2 + (centroidY - y2) * (halfStroke / distance(x2, y2, centroidX, centroidY))});
        shape.setPoint(2, {x3 + (centroidX - x3) * (halfStroke / distance(x3, y3, centroidX, centroidY)),
                           y3 + (centroidY - y3) * (halfStroke / distance(x3, y3, centroidX, centroidY))});
    } else {
        shape.setPoint(0, {x1, y1});
        shape.setPoint(1, {x2, y2});
        shape.setPoint(2, {x3, y3});
    }

    set_position_fill_stroke(shape, {0, 0});
    g_window->draw(shape);
}

void seal::ellipseMode(seal::EllipseMode mode) { g_currentEllipseMode = mode; }

void seal::strokeWeight(float weight) { g_currentStrokeWeight = weight; }
