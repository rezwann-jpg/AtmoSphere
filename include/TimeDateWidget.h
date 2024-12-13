#ifndef TIMEDATEWIDGET_H
#define TIMEDATEWIDGET_H

#pragma once

#include "UIElement.h"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

class TimeDateWidget : public UIElement {
public:
    TimeDateWidget(const sf::Vector2f& pos, const sf::Vector2f& sz);
    ~TimeDateWidget();

    void Draw(sf::RenderWindow& window) override;
    void Update(const sf::Vector2f& mousePos) override;
    bool HandleEvent(const sf::Event& e) override;

private:
    sf::Font font;
    sf::Text timeText;
    sf::Text dateText;

    void updateTime();
};

#endif