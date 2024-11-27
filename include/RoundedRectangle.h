#ifndef ROUNDEDRECTANGLE_H
#define ROUNDEDRECTANGLE_H

#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

const std::size_t CORNER_POINTS = 16;
const float PI = 3.141592654;

class RoundedRectangle : public sf::Shape {
public:
    RoundedRectangle(sf::Vector2f size = {0, 0}, float radius = 0);

    void setSize(sf::Vector2f size);
    sf::Vector2f getSize() const;
    void setRadius(float radius);
    float getRadius() const;
    void setCornerPointCount(std::size_t cornerPointCount);
    std::size_t getCornerPointCount() const;

    std::size_t getPointCount() const override;
    sf::Vector2f getPoint(std::size_t index) const override;
    
private:
    sf::Vector2f size;
    std::size_t cornerPointCount;
    float anglePerPoint;
    float cornerRadius;

};

#endif