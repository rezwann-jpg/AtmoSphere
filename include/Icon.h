#ifndef ICON_H
#define ICON_H

#pragma once

#include <SFML/Graphics.hpp>

class Icon {
public:
    Icon();
    ~Icon();

    bool loadFromFile(const std::string& filePath);
    sf::Sprite& getSprite();
    sf::Texture& getTexture();

private:
    sf::Texture texture;
    sf::Sprite sprite;

};

#endif