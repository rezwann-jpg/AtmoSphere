#include "Icon.h"
#include <iostream>

Icon::Icon() {}
Icon::~Icon() {}

bool Icon::loadFromFile(const std::string &filePath) {
    if (!texture.loadFromFile(filePath)) {
        std::cerr << "Failed to load icon from: " << filePath << std::endl;
        return false; 
    }
    sprite.setTexture(texture, true);
    return true;
}

sf::Texture& Icon::getTexture() {
    return texture;
}

sf::Sprite& Icon::getSprite() {
    return sprite;
}
