#include "ellipse.hpp"

EllipseShape::EllipseShape(sf::Vector2f radius) : radius(radius) { update(); }

std::size_t EllipseShape::getPointCount() const { return 30; }

sf::Vector2f EllipseShape::getPoint(std::size_t index) const {
    static constexpr float pi = 3.141592654f;
    static constexpr float half_pi = pi / 2;
    float angle = index * 2 * pi / getPointCount() - half_pi;
    float x = std::cos(angle) * radius.x;
    float y = std::sin(angle) * radius.y;

    return radius + sf::Vector2f(x, y);
}
