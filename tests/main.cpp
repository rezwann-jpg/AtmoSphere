#include <SFML/Graphics.hpp>
#include "cityWeather.h"
#include "cityManager.h"
#include "weatherDashboard.h"
#include <iostream>

DetailedWeather createSampleWeather(double temp, double wind, int humidity, time_t sunrise, time_t sunset) {
    DetailedWeather weather;
    weather.setTemperature(temp);
    weather.setWindSpeed(wind);
    weather.setHumidity(humidity);
    weather.setSunrise(sunrise);
    weather.setSunset(sunset);
    weather.setWeatherMain("Clear");
    weather.setWeatherDescription("Clear sky");
    return weather;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Weather Dashboard Demo");

    std::string currCity;
    std::vector<std::string> savedCities;

    SearchBar search(
        sf::Vector2f(20, 20),
        sf::Vector2f(300, 40),
        [&currCity](const std::string& city) {
            std::cout << "Searching for " << city << std::endl;
            currCity = city;
        }
    );

    Button save(
        sf::Vector2f(370, 20),
        sf::Vector2f(150, 40),
        "Save City",
        [&currCity, &savedCities]() {
            if (!currCity.empty()) {
                savedCities.push_back(currCity);
                std::cout << "Saved" << currCity << "\n";
            }
        }
    );
    
    CityManager cityManager;
    
    auto london = std::make_unique<CityWeather>();
    london->setCityName("London");
    london->setCountryCode("UK");
    london->setLatitude(51.5074);
    london->setLongitude(-0.1278);
    london->updateWeather(createSampleWeather(291.5, 4.2, 65, 1653456789, 1653496789));
    
    auto newYork = std::make_unique<CityWeather>();
    newYork->setCityName("New York");
    newYork->setCountryCode("US");
    newYork->setLatitude(40.7128);
    newYork->setLongitude(-74.0060);
    newYork->updateWeather(createSampleWeather(295.1, 5.8, 58, 1653456789, 1653496789));
    
    auto tokyo = std::make_unique<CityWeather>();
    tokyo->setCityName("Tokyo");
    tokyo->setCountryCode("JP");
    tokyo->setLatitude(35.6762);
    tokyo->setLongitude(139.6503);
    tokyo->updateWeather(createSampleWeather(298.3, 3.1, 72, 1653456789, 1653496789));

    cityManager.addCity(std::move(london));
    cityManager.addCity(std::move(newYork));
    cityManager.addCity(std::move(tokyo));

    try {
        WeatherDashboard dashboard(sf::Vector2f(20, 80), cityManager, window);
        
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
                save.HandleEvent(event);
            }

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

            search.Update(mousePosF);
            save.Update(mousePosF);
            dashboard.Update();

            window.clear(sf::Color::White);
            dashboard.drawAll();
            search.Draw(window);
            save.Draw(window);
            window.display();
        }
    }
    catch(const WeatherException& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

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