#ifndef WEATHERDASHBOARD_H
#define WEATHERDASHBOARD_H

#pragma once

#include <SFML/Graphics.hpp>
#include "cityManager.h"
#include "WeatherCard.h"
#include "Button.h"
#include "SearchBar.h"
#include <vector>
#include <memory>

class WeatherDashboard {
public:
    WeatherDashboard(const sf::Vector2f& pos, CityManager& cm, sf::RenderWindow& win);
    ~WeatherDashboard();

    void refreshDashboard();
    void arrangeGrid();
    void showDetailedView(CityWeather* city);
    void drawAll();
    void handleResize();
    void handleEvents(const sf::Event& event);

    void updateWeather();
    
    void Update(const sf::Vector2f &mousePos);
    
private:
    void deleteCity(CityWeather* city);
    
    CityManager& cityManager;
    sf::RenderWindow& window;
    sf::Font font;
    std::vector<std::unique_ptr<WeatherCard>> cards;
    sf::Vector2f gridMargin;
    float columnSpacing = 25.f;
    float rowSpacing = 25.f;
    sf::Vector2f cardBaseSize {260, 190};
    int columns = 3;

};

std::string windDirectionToString(int degree);

#endif