#ifndef APP_H
#define APP_H

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "WeatherService.h"
#include "cityManager.h"
#include "UIElement.h"
#include "WeatherDashboard.h"

class App {
public:
    App(const std::string& title, int width, int height);
    ~App();

    bool Running();
    void HandleEvents();
    void Update();
    void Draw();

private:
    sf::RenderWindow window;
    WeatherService service;
    CityManager cityManager;
    std::vector<UIElement*> elements;
    WeatherDashboard dashboard;
};

#endif