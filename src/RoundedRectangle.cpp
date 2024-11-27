#include "RoundedRectangle.h"

RoundedRectangle::RoundedRectangle(sf::Vector2f size, float radius) : size(size), cornerRadius(radius) {
    setCornerPointCount(CORNER_POINTS);
    update();
}

void RoundedRectangle::setSize(sf::Vector2f size) {
    this->size = size;
    update();
}

sf::Vector2f RoundedRectangle::getSize() const {
    return size;
}

void RoundedRectangle::setRadius(float radius) {
    this->cornerRadius = radius;
    update();
}

float RoundedRectangle::getRadius() const {
    return cornerRadius;
}

void RoundedRectangle::setCornerPointCount(std::size_t cornerPointCount) {
    this->cornerPointCount = cornerPointCount;
    this->anglePerPoint = 90.0f / cornerPointCount;
    update();
}

std::size_t RoundedRectangle::getCornerPointCount() const {
    return cornerPointCount;
}

std::size_t RoundedRectangle::getPointCount() const {
    return cornerPointCount * 4;
}

sf::Vector2f RoundedRectangle::getPoint(std::size_t index) const {
    if (cornerPointCount == 1 || cornerRadius == 0.0f) {
        sf::RectangleShape rect(size);
        return rect.getPoint(index);
    }
    else {
        std::size_t corner = index / cornerPointCount;
        float angle = 0.0f;
        bool isLastPointOnCorner = (index % cornerPointCount == cornerPointCount - 1);
        if (isLastPointOnCorner) {
            angle = 90.0f;
        }
        else {
            angle = (index % cornerPointCount) * cornerPointCount;
        }
        sf::Vector2f point;
        switch (corner) {
            case 0:
                point = {cornerRadius, cornerRadius};
                angle -= 180;
                break;

            case 1:
                point = {size.x - cornerRadius, cornerRadius};
                angle -= 90;
                break;

            case 2:
                point = {size.x - cornerRadius, size.y - cornerRadius};
                break;

            default:
                point = {cornerRadius, size.y - cornerRadius};
                angle += 90;
        }
        point += {cosf(angle * PI / 180) * cornerRadius, sinf(angle * PI / 180) * cornerRadius};
        return point;
    }
}