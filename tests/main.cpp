#include "Button.h"
#include "SearchBar.h"
#include "RoundedRectangle.h"
#include "TimeDateWidget.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

int main() {
    sf::RenderWindow window(sf::VideoMode(736, 1000), "Demo");

    std::string currCity;
    std::vector<std::string> savedCities;

    TimeDateWidget timeWidget(
        sf::Vector2f(50, 500),
        sf::Vector2f(200, 50)
    );
    
    SearchBar search(
        sf::Vector2f(50, 50),
        sf::Vector2f(300, 40),
        [&currCity](const std::string& city) {
            std::cout << "Searching for " << city << std::endl;
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