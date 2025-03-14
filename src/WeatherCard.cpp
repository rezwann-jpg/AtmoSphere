#include "WeatherCard.h"
#include "IconManager.h"
#include <cmath>
#include <sstream>
#include <iostream>

WeatherCard::WeatherCard(const sf::Vector2f &pos, const sf::Vector2f &sz, CityWeather *city, const sf::Font &font, std::function<void(CityWeather *)> clickHandler) 
    : cityData(city), onClick(clickHandler), UIElement(pos, sz) {
    
    background.setFillColor(sf::Color(240, 240, 240));

    cityNameText.setFont(font);
    tempText.setFont(font);
    mainText.setFont(font);
    windText.setFont(font);

    updateChildPositions();
    updateDisplay();
}

WeatherCard::~WeatherCard() {}

void WeatherCard::setPosition(const sf::Vector2f &pos) {
    UIElement::setPosition(pos);
    updateChildPositions();
}

void WeatherCard::setSize(const sf::Vector2f &sz) {
    UIElement::setSize(sz);
    updateChildPositions();
}

void WeatherCard::updateDisplay() {
    if (!cityData)
        return;

    cityNameText.setString(cityData->getCityName());
    std::stringstream tempSS;
    tempSS.precision(0);
    tempSS << std::fixed << cityData->getWeather().getTemperature();
    std::string tempStr = tempSS.str() + "\xC2\xB0" + "C";
    tempText.setString(sf::String::fromUtf8(tempStr.begin(), tempStr.end()));
    mainText.setString(cityData->getWeather().getWeatherMain());
    std::stringstream windSS;
    windSS.precision(1);
    windSS << "Wind: " << std::fixed << cityData->getWeather().getWindSpeed() << " m/s";
    windText.setString(windSS.str());
}

bool WeatherCard::HandleEvent(const sf::Event &e) {
    if(e.type == sf::Event::MouseButtonPressed) {
        if (isHovered) {
            if (onClick) onClick(cityData);
            return true;
        }
    }
    return false;
}

void WeatherCard::Update(const sf::Vector2f &mousePos) {
    isHovered = background.getGlobalBounds().contains(mousePos);
    
    if (isHovered) {
        background.setFillColor(sf::Color(220, 230, 255));
        cityNameText.setFillColor(sf::Color(0, 0, 100));
    } else {
        background.setFillColor(sf::Color(234, 242, 255));
        cityNameText.setFillColor(sf::Color(30, 30, 30));
    }

    updateDisplay();
}

void WeatherCard::Draw(sf::RenderWindow &window) {
    window.draw(background);
    window.draw(cityNameText);
    window.draw(tempText);
    window.draw(mainText);
    window.draw(windText);
    window.draw(iconPlaceholder);
}

sf::FloatRect WeatherCard::getGlobalBounds() const {
    return sf::FloatRect(position, size);
}

void WeatherCard::updateChildPositions() {
    background.setPosition(position);
    background.setSize(size);
    background.setRadius(20);
    background.setFillColor(sf::Color(234, 242, 255));
    // background.setOutlineColor(sf::Color(200, 200, 200));
    // background.setOutlineThickness(1.f);
    
    auto centerText = [&](sf::Text& text, float verticalOffset) {
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width/2.0f,
                      textBounds.top + textBounds.height/2.0f);
        text.setPosition(position.x + size.x/2.0f, 
                        position.y + size.y * verticalOffset);
    };
    cityNameText.setCharacterSize(20);
    cityNameText.setFillColor(sf::Color(30, 30, 30));
    centerText(cityNameText, 0.2f);

    tempText.setCharacterSize(24);
    tempText.setStyle(sf::Text::Bold);
    tempText.setFillColor(sf::Color(10, 50, 150));
    centerText(tempText, 0.4f);

    mainText.setCharacterSize(16);
    mainText.setFillColor(sf::Color(80, 80, 80));
    centerText(mainText, 0.6f);

    windText.setCharacterSize(16);
    windText.setFillColor(sf::Color(80, 80, 80));
    centerText(windText, 0.7f);

    std::string weatherKey = cityData->getWeather().getWeatherMain();
    iconPlaceholder = TheIconManager::getInstance().getIcon(weatherKey);

    iconPlaceholder.setPosition(
        position.x + size.x - 70,
        position.y + 20
    );
}