#ifndef WEATHERCARD_H
#define WEATHERCARD_H

#pragma once

#include "UIElement.h"
#include "cityWeather.h"
#include "RoundedRectangle.h"
#include <functional>

class WeatherCard : public UIElement {
public:
    WeatherCard(const sf::Vector2f &pos, const sf::Vector2f &sz, CityWeather* city, const sf::Font& font, std::function<void(CityWeather*)>clickHandler, std::function<void(CityWeather*)> deleteHandle);
    ~WeatherCard();

    void setPosition(const sf::Vector2f& pos) override;
    void setSize(const sf::Vector2f& sz) override;

    bool HandleEvent(const sf::Event& e) override;
    void Update(const sf::Vector2f& mousePos = {0, 0}) override;
    void Draw(sf::RenderWindow& window) override;
    
    sf::FloatRect getGlobalBounds() const;
    
private:
    CityWeather* cityData;
    RoundedRectangle background;
    sf::Text cityNameText;
    sf::Text tempText;
    sf::Text mainText;
    sf::Text windText;
    sf::Sprite iconPlaceholder;

    sf::CircleShape deleteButton;
    sf::Text deleteButtonText;

    bool isDeleteHovered;
    
    std::function<void(CityWeather*)> onClick;
    std::function<void(CityWeather*)> onDelete;
    
    void updateDisplay();
    void updateChildPositions();
};

#endif