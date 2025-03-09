#include "Icon.h"
#include <iostream>

Icon::Icon() {}
Icon::~Icon() {}

bool Icon::loadFromFile(const std::string &filePath) {
    if (!texture.loadFromFile(filePath)) {
        std::cerr << "Failed to load icon from: " << filePath << std::endl;
        return false; 
    }
    sprite.setTexture(texture);
    return true;
}

sf::Sprite Icon::getSprite() const {
    return sprite;
}
