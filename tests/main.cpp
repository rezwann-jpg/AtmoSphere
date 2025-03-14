#include "App.h"

int main() {
    App app("AtmoSphere", 1280, 720);

    while (app.Running()) {
        app.HandleEvents();
        app.Update();
        app.Draw();
    }

    return 0;
}

/*#include <SFML/Graphics.hpp>
#include "cityWeather.h"
#include "cityManager.h"
#include "weatherDashboard.h"
#include "WeatherService.h"
#include "IconManager.h"
#include "TimeDateWidget.h"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Weather Dashboard Demo");

    std::string currCity;
    std::vector<std::string> savedCities;

    WeatherService ws("99cf5d3f3e51411bb01ed89e384a01a4");
    CityManager cityManager;

    if (!TheIconManager::getInstance().load()) {
        std::cerr << "Failed to load icons" << std::endl;
    }

    SearchBar search(
        sf::Vector2f(100, 20),
        sf::Vector2f(300, 40),
        [&currCity, &cityManager, &ws](const std::string& city) {
            std::cout << "Searching for " << city << std::endl;
            auto cityW = std::make_unique<CityWeather>();
            *cityW = ws.getWeatherForCity(city);
            std::cout << cityW->getWeather().getWeatherMain() << "\n";
            cityManager.addCity(std::move(cityW));
            currCity = city;
        }
    );

    TimeDateWidget tdw(
        sf::Vector2f(600, 20),
        sf::Vector2f(200, 50)
    );

    try {
        WeatherDashboard dashboard(sf::Vector2f(20, 80), cityManager, window);

        Button refresh(
            sf::Vector2f(470, 20),
            sf::Vector2f(150, 40),
            "Refresh",
            [&dashboard]() {
                dashboard.updateWeather();
                std::cout << "Refreshed all data\n";
            }
        );
        
        while(window.isOpen()) {
            sf::Event event;
            while(window.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    window.close();
                }
                else if(event.type == sf::Event::Resized) {
                    sf::FloatRect visibleArea(0, 0, 
                        static_cast<float>(event.size.width), 
                        static_cast<float>(event.size.height));
                    window.setView(sf::View(visibleArea));
                    dashboard.handleResize();
                }

                search.HandleEvent(event);
                refresh.HandleEvent(event);
                dashboard.handleEvents(event);
                tdw.HandleEvent(event);
            }

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

            search.Update(mousePosF);
            refresh.Update(mousePosF);
            dashboard.Update(mousePosF);
            tdw.Update(mousePosF);

            window.clear(sf::Color::White);
            dashboard.drawAll();
            search.Draw(window);
            refresh.Draw(window);
            tdw.Draw(window);
            window.display();
        }
    }
    catch(const WeatherException& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }

    TheIconManager::getInstance().cleanUp();

    return 0;
}
*/
/*
#include "Button.h"
#include "SearchBar.h"
#include "RoundedRectangle.h"
#include "TimeDateWidget.h"
#include "WeatherFetcher.h"
#include "BaseFetcher.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

int main() {
    sf::RenderWindow window(sf::VideoMode(736, 1000), "Demo");

    BaseFetcher *fetcher = new WeatherFetcher("99cf5d3f3e51411bb01ed89e384a01a4");

    std::string currCity;
    std::vector<std::string> savedCities;

    TimeDateWidget timeWidget(
        sf::Vector2f(50, 500),
        sf::Vector2f(200, 50)
    );
    
    SearchBar search(
        sf::Vector2f(50, 50),
        sf::Vector2f(300, 40),
        [&currCity, fetcher](const std::string& city) {
            std::cout << "Searching for " << city << std::endl;
            std::cout << fetcher->fetchData(city) << std::endl;
            currCity = city;
        }
    );

    Button save(
        sf::Vector2f(370, 50),
        sf::Vector2f(150, 40),
        "Save City",
        [&currCity, &savedCities]() {
            if (!currCity.empty()) {
                savedCities.push_back(currCity);
                std::cout << "Saved" << currCity << "\n";
            }
        }
    );

    Button showSave(
        sf::Vector2f(50, 110),
        sf::Vector2f(200, 40),
        "Show Saved Cities",
        [&savedCities]() {
            std::cout << "Saved cities" << std::endl;
            for (auto city : savedCities) {
                std::cout << "- " << city << "\n";
            }
        }
    );

    RoundedRectangle rect(
        sf::Vector2f(150, 40),
        20
    );
    rect.setPosition(sf::Vector2f(270, 110));
    rect.setFillColor(sf::Color::Green);
    // rect.setOutlineColor(sf::Color::Black);
    // rect.setOutlineThickness(2);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/download.jpg")) {
        throw std::runtime_error("Failed to load image");
    }

    sf::Sprite backgroundSprite(backgroundTexture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                bool pressed = rect.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                std::cout << (pressed ? "Pressed\n" : "");
            }

            search.HandleEvent(event);
            save.HandleEvent(event);
            showSave.HandleEvent(event);
            timeWidget.HandleEvent(event);
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        search.Update(mousePosF);
        save.Update(mousePosF);
        showSave.Update(mousePosF);
        timeWidget.Update(mousePosF);
        
        window.clear();
        window.draw(backgroundSprite);
        save.Draw(window);
        showSave.Draw(window);
        window.draw(rect);
        search.Draw(window);
        timeWidget.Draw(window);
        window.display();
    }

    return 0;
}
*/
/*
#include <SFML/Network.hpp>
#include <iostream>
#include <string>

int main() {
    sf::Http http("http://api.openweathermap.org");

    std::string apiKey = "99cf5d3f3e51411bb01ed89e384a01a4";
    std::string city = "Dhaka";
    std::string endpoint = "/data/2.5/weather?q=" + city + "&appid=" + apiKey;

    sf::Http::Request request(endpoint, sf::Http::Request::Get);

    sf::Http::Response response = http.sendRequest(request);

    if (response.getStatus() == sf::Http::Response::Ok) {
        std::cout << "Response received successfully!" << std::endl;
        std::cout << "Data: " << response.getBody() << std::endl;
    } else {
        std::cerr << "HTTP error: " << response.getStatus() << std::endl;
    }

    return 0;
}
*/