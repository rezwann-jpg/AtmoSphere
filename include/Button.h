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

    void Draw(sf::RenderWindow& window) override;
    void Update(const sf::Vector2f& mousePos) override;
    bool HandleEvent(const sf::Event& e) override;

    void SetLabel(const std::string &label);
    void SetActive(bool active);
    bool IsActive() const;
    void SetPosition(const sf::Vector2f &pos);
    void SetSize(const sf::Vector2f &sz);
    void SetColors(const sf::Color &normal, const sf::Color &hover, const sf::Color &pressed);

private:
    void UpdateVisuals();
    void CenterText();

    RoundedRectangle shape;

    sf::Text text;
    sf::Font font;
    std::function<void()> onClick;

    bool isPressed;
    bool isActive;

    sf::Color normalColor = sf::Color(60, 60, 220);
    sf::Color hoverColor = sf::Color(80, 80, 230);
    sf::Color pressedColor = sf::Color(40, 40, 180);
};

#endif