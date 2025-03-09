#include "WeatherCard.h"
#include <cmath>
#include <sstream>

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
    tempSS.precision(2);
    tempSS << cityData->getWeather().getTemperature() << "\u00B0C";
    tempText.setString(tempSS.str());
    mainText.setString(cityData->getWeather().getWeatherMain());
    std::stringstream windSS;
    windSS.precision(2);
    windSS << "Wind: " << cityData->getWeather().getWindSpeed() << " m/s";
    windText.setString(windSS.str());

}

bool WeatherCard::HandleEvent(const sf::Event &e) {
    if(e.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(e.mouseButton.x, e.mouseButton.y);
        if(background.getGlobalBounds().contains(mousePos)) {
            if(onClick) onClick(cityData);
            return true;
        }
    }
    return false;
}

void WeatherCard::Update(const sf::Vector2f &mousePos) {
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

    tempText.setCharacterSize(18);
    tempText.setStyle(sf::Text::Bold);
    tempText.setFillColor(sf::Color(10, 50, 150));
    centerText(tempText, 0.4f);

    mainText.setCharacterSize(16);
    mainText.setFillColor(sf::Color(80, 80, 80));
    centerText(mainText, 0.6f);

    windText.setCharacterSize(16);
    windText.setFillColor(sf::Color(80, 80, 80));
    centerText(windText, 0.7f);

    iconPlaceholder.setSize({40, 40});
    iconPlaceholder.setPosition(
        position.x + size.x - 50,
        position.y + 10
    );
    iconPlaceholder.setFillColor(sf::Color(200, 230, 255));
}