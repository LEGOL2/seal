#pragma once

#include <SFML/Graphics.hpp>

class EllipseShape : public sf::CircleShape {
   public:
    explicit EllipseShape(sf::Vector2f radius);

    std::size_t getPointCount() const override;
    sf::Vector2f getPoint(std::size_t index) const override;

   private:
    sf::Vector2f radius;
};
