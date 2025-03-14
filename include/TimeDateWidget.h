#ifndef TIMEDATEWIDGET_H
#define TIMEDATEWIDGET_H

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <iostream>
#include "UIElement.h"

struct WidgetTheme {
    sf::Color primaryColor = sf::Color::White;
    sf::Color secondaryColor = sf::Color(200, 200, 200);
    sf::Color accentColor = sf::Color(255, 215, 0);
    float outlineThickness = 2.0f;
};

class TimeDateWidget : public UIElement {
public:
    TimeDateWidget(const sf::Vector2f &pos, const sf::Vector2f &sz);
    virtual ~TimeDateWidget();
    
    virtual void Draw(sf::RenderWindow &window) override;
    virtual void Update(const sf::Vector2f &mousePos) override;
    virtual bool HandleEvent(const sf::Event &e) override;
    
    void setTheme(const WidgetTheme& theme);
    void setTimeFormat(const std::string& format);
    void setDateFormat(const std::string& format);
    
private:
    sf::Font font;
    sf::Text timeText;
    sf::Text dateText;
    sf::Clock updateClock;
    std::string timeFormat;
    std::string dateFormat;
    
    void setupVisuals();
    void initializeTimer();
    void updateTime();
};

#endif