#ifndef UIELEMENT_H
#define UIELEMENT_H

#pragma once

#include <SFML/Graphics.hpp>

class UIElement
{
public:
    UIElement(const sf::Vector2f& pos, const sf::Vector2f& sz);
    ~UIElement();

    virtual void Draw(sf::RenderWindow& window) = 0;
    virtual void Update(const sf::Vector2f& mousePos) = 0;
    virtual bool HandleEvent(const sf::Event& e) = 0;

    virtual void setPosition(const sf::Vector2f& pos);
    virtual void setSize(const sf::Vector2f& sz);
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;

protected:
    sf::Vector2f position;
    sf::Vector2f size;
    bool isHovered;

};

#endif