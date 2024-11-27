#ifndef BUTTON_H
#define BUTTON_H

#pragma once

#include "UIElement.h"
#include "RoundedRectangle.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

class Button : public UIElement {
public:
    Button(const sf::Vector2f& pos, const sf::Vector2f& sz, const std::string& label, const std::function<void()>& callback);
    ~Button();

    // TODO no arg constructor

    void UpdateVisuals();
    void Draw(sf::RenderWindow& window) override;
    void Update(const sf::Vector2f& mousePos) override;
    bool HandleEvent(const sf::Event& e) override;

private:
    RoundedRectangle shape;
    sf::Text text;
    sf::Font font;
    std::function<void()> onClick;
    bool isPressed;

};

#endif