#include "UIElement.h"

UIElement::UIElement(const sf::Vector2f &pos, const sf::Vector2f &sz) : position(pos), size(sz), isHovered(false) { }

UIElement::~UIElement() {}

void UIElement::setPosition(const sf::Vector2f &pos) {
    position = pos;
}

void UIElement::setSize(const sf::Vector2f &sz) {
    size = sz;
}

sf::Vector2f UIElement::getPosition() const {
    return position;
}

sf::Vector2f UIElement::getSize() const {
    return size;
}
