#include "WeatherDashboard.h"
#include "IconManager.h"
#include <set>
#include <sstream>
#include <ctime>
#include <iomanip>

WeatherDashboard::WeatherDashboard(const sf::Vector2f& pos, CityManager& cm, sf::RenderWindow& win) : gridMargin(pos), cityManager(cm), window(win) {
    if(!font.loadFromFile("assets/DMSans-Regular.ttf")) {
        throw WeatherException("Font loading failed");
    }
    
    cityManager.addObserver([this]() { refreshDashboard(); });

    refreshDashboard();
}

WeatherDashboard::~WeatherDashboard() {}

void WeatherDashboard::refreshDashboard() {
    auto cityNames = cityManager.getAllCityNames();

    // if (cityNames.empty()) {
    //     cards.clear();
    //     auto city = std::make_unique<CityWeather>();
    //     auto placeholderCard = std::make_unique<WeatherCard>(
    //         sf::Vector2f(0, 0),
    //         cardBaseSize,
    //         city.get(),
    //         font,
    //         [this](CityWeather *city) { std::cout << "Nothing to show here\n"; }
    //     );
    //     city->setCityName("No cities available.");
    //     cards.push_back(std::move(placeholderCard));
    //     handleResize();
    //     return;
    // }

    std::set<std::string> uniqueCities;
    std::vector<std::unique_ptr<WeatherCard>> newCards;

    for (const auto& name : cityNames) {
        if (uniqueCities.count(name)) continue;
        uniqueCities.insert(name);

        auto* city = cityManager.getCityByName(name);
        if (!city) {
            std::cerr << "Warning: City data not found for " << name << "\n";
            continue;
        }

        auto card = std::make_unique<WeatherCard>(
            sf::Vector2f(0, 0),
            cardBaseSize,
            city,
            font,
            [this](CityWeather* city) { showDetailedView(city); }
        );
        newCards.push_back(std::move(card));
    }
    cards = std::move(newCards);

    handleResize();
}

void WeatherDashboard::arrangeGrid() {
    if(cards.empty()) return;
        
    const auto& cardSize = cards[0]->getSize();
    
    sf::Vector2f currentPos = gridMargin;
    
    for(size_t i = 0; i < cards.size(); i++) {
        cards[i]->setPosition(currentPos);
        cards[i]->setSize(cardSize);

        currentPos.x += cardSize.x + columnSpacing;

        if((i + 1) % columns == 0 && i != 0) {
            currentPos.x = gridMargin.x;
            currentPos.y += cardSize.y + rowSpacing;
        }
    }
}

void WeatherDashboard::showDetailedView(CityWeather *city) {
    if (!city) return;

    bool isOpen = true;
    sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));

    sf::RectangleShape detailsBox(sf::Vector2f(500, 450));
    detailsBox.setFillColor(sf::Color(245, 245, 250));
    detailsBox.setOutlineThickness(0);
    detailsBox.setPosition((window.getSize().x - detailsBox.getSize().x) / 2,
                         (window.getSize().y - detailsBox.getSize().y) / 2);

    sf::RectangleShape headerBar(sf::Vector2f(detailsBox.getSize().x, 60));
    headerBar.setFillColor(sf::Color(60, 100, 170));
    headerBar.setPosition(detailsBox.getPosition().x, detailsBox.getPosition().y);

    const DetailedWeather& weather = city->getWeather();

    sf::Sprite weatherIcon = TheIconManager::getInstance().getIcon(city->getWeather().getWeatherMain());
    weatherIcon.setPosition(
        detailsBox.getPosition().x + detailsBox.getSize().x - 100,
        headerBar.getPosition().y + 10
    );

    sf::RectangleShape closeButton(sf::Vector2f(30, 30));
    closeButton.setFillColor(sf::Color(200, 60, 60));
    closeButton.setPosition(
        detailsBox.getPosition().x + detailsBox.getSize().x - 40,
        detailsBox.getPosition().y + 15
    );

    sf::Text cityName(city->getCityName() + ", " + city->getCountryCode(), font, 26);
    cityName.setStyle(sf::Text::Bold);
    cityName.setFillColor(sf::Color::White);
    cityName.setPosition(detailsBox.getPosition().x + 25, headerBar.getPosition().y + 15);

    const std::string degreeSymbol = "\xC2\xB0";

    std::ostringstream tempStream;
    tempStream << std::fixed << std::setprecision(1) << weather.getTemperature();

    std::string tempStr = tempStream.str() + degreeSymbol + "C";

    sf::Text tempLarge(sf::String::fromUtf8(tempStr.begin(), tempStr.end()), font, 48);
    tempLarge.setStyle(sf::Text::Bold);
    tempLarge.setFillColor(sf::Color(40, 40, 100));
    tempLarge.setPosition(detailsBox.getPosition().x + 25, headerBar.getPosition().y + 80);
    
    sf::Text condition(weather.getWeatherDescription(), font, 22);
    condition.setFillColor(sf::Color(80, 80, 80));
    condition.setPosition(detailsBox.getPosition().x + 25, tempLarge.getPosition().y + 60);

    sf::Vector2f gridStart(detailsBox.getPosition().x + 25, condition.getPosition().y + 50);
    float rowHeight = 40;
    float colWidth = 230;
    
    sf::Text humidity("Humidity", font, 18);
    humidity.setFillColor(sf::Color(100, 100, 100));
    humidity.setPosition(gridStart.x, gridStart.y);
    
    sf::Text humidityValue(std::to_string(weather.getHumidity()) + "%", font, 20);
    humidityValue.setStyle(sf::Text::Bold);
    humidityValue.setFillColor(sf::Color::Black);
    humidityValue.setPosition(gridStart.x, gridStart.y + 22);
    
    sf::Text wind("Wind Speed", font, 18);
    wind.setFillColor(sf::Color(100, 100, 100));
    wind.setPosition(gridStart.x, gridStart.y + rowHeight);
    
    std::ostringstream windStream;
    windStream << std::fixed << std::setprecision(1) << weather.getWindSpeed();
    sf::Text windValue(windStream.str() + " m/s", font, 20);
    windValue.setStyle(sf::Text::Bold);
    windValue.setFillColor(sf::Color::Black);
    windValue.setPosition(gridStart.x, gridStart.y + rowHeight + 22);
    
    sf::Text windDir("Wind Direction", font, 18);
    windDir.setFillColor(sf::Color(100, 100, 100));
    windDir.setPosition(gridStart.x, gridStart.y + rowHeight * 2);

    std::string directionText = windDirectionToString(weather.getWindDegree());
    std::string directionStr = std::to_string(static_cast<int>(weather.getWindDegree())) + degreeSymbol + " " + directionText;
    sf::Text windDirValue(sf::String::fromUtf8(directionStr.begin(), directionStr.end()), font, 20);
    windDirValue.setStyle(sf::Text::Bold);
    windDirValue.setFillColor(sf::Color::Black);
    windDirValue.setPosition(gridStart.x, gridStart.y + rowHeight * 2 + 22);
    
    sf::Text cloudiness("Cloudiness", font, 18);
    cloudiness.setFillColor(sf::Color(100, 100, 100));
    cloudiness.setPosition(gridStart.x + colWidth, gridStart.y);
    
    sf::Text cloudinessValue(std::to_string(weather.getCloudiness()) + "%", font, 20);
    cloudinessValue.setStyle(sf::Text::Bold);
    cloudinessValue.setFillColor(sf::Color::Black);
    cloudinessValue.setPosition(gridStart.x + colWidth, gridStart.y + 22);
    
    sf::Text visibility("Visibility", font, 18);
    visibility.setFillColor(sf::Color(100, 100, 100));
    visibility.setPosition(gridStart.x + colWidth, gridStart.y + rowHeight);
    
    std::ostringstream visStream;
    visStream << std::fixed << std::setprecision(1) << (weather.getVisibility() / 1000.0f);
    sf::Text visibilityValue(visStream.str() + " km", font, 20);
    visibilityValue.setStyle(sf::Text::Bold);
    visibilityValue.setFillColor(sf::Color::Black);
    visibilityValue.setPosition(gridStart.x + colWidth, gridStart.y + rowHeight + 22);
    
    sf::RectangleShape timelineBar(sf::Vector2f(detailsBox.getSize().x - 50, 2));
    timelineBar.setFillColor(sf::Color(200, 200, 200));
    timelineBar.setPosition(detailsBox.getPosition().x + 25, gridStart.y + rowHeight * 3 + 30);
    
    sf::Sprite sunriseIcon = TheIconManager::getInstance().getIcon("Sunrise");
    sunriseIcon.setPosition(detailsBox.getPosition().x + 30, timelineBar.getPosition().y + 15);
    sunriseIcon.setScale(0.5f, 0.5f);
    
    sf::Sprite sunsetIcon = TheIconManager::getInstance().getIcon("Sunset");
    sunsetIcon.setPosition(detailsBox.getPosition().x + detailsBox.getSize().x - 70, timelineBar.getPosition().y + 15);
    sunsetIcon.setScale(0.5f, 0.5f);
    
    std::ostringstream sunriseStr, sunsetStr;
    time_t sunriseTimeT = weather.getSunrise();
    time_t sunsetTimeT = weather.getSunset();
    struct tm* sunriseTime = localtime(&sunriseTimeT);
    struct tm* sunsetTime = localtime(&sunsetTimeT);

    sunriseStr << std::setfill('0') << std::setw(2) << sunriseTime->tm_hour << ":"
               << std::setw(2) << sunriseTime->tm_min;
    sunsetStr << std::setfill('0') << std::setw(2) << sunsetTime->tm_hour << ":"
              << std::setw(2) << sunsetTime->tm_min;

    sf::Text sunrise(sunriseStr.str(), font, 18);
    sunrise.setFillColor(sf::Color::Black);
    sunrise.setPosition(sunriseIcon.getPosition().x + sunriseIcon.getGlobalBounds().width + 5, 
                      sunriseIcon.getPosition().y - 5);
    
    sf::Text sunset(sunsetStr.str(), font, 18);
    sunset.setFillColor(sf::Color::Black);
    sunset.setPosition(sunsetIcon.getPosition().x - sunset.getGlobalBounds().width - 5,
                     sunsetIcon.getPosition().y - 5);
    
    sf::Text pressure("Pressure", font, 18);
    pressure.setFillColor(sf::Color(100, 100, 100));
    pressure.setPosition(gridStart.x + colWidth, gridStart.y + rowHeight * 2);
    
    sf::Text pressureValue(std::to_string(weather.getPressure()) + " hPa", font, 20);
    pressureValue.setStyle(sf::Text::Bold);
    pressureValue.setFillColor(sf::Color::Black);
    pressureValue.setPosition(gridStart.x + colWidth, gridStart.y + rowHeight * 2 + 22);
    
    sf::RectangleShape footerDivider(sf::Vector2f(detailsBox.getSize().x, 1));
    footerDivider.setFillColor(sf::Color(200, 200, 200));
    footerDivider.setPosition(detailsBox.getPosition().x, 
                             detailsBox.getPosition().y + detailsBox.getSize().y - 40);
    
    time_t now = time(nullptr);
    struct tm* currentTime = localtime(&now);
    std::ostringstream lastUpdated;
    lastUpdated << "Updated at: " << std::setfill('0') << std::setw(2) << currentTime->tm_hour << ":"
                << std::setw(2) << currentTime->tm_min;
    
    sf::Text updatedAt(lastUpdated.str(), font, 16);
    updatedAt.setFillColor(sf::Color(120, 120, 120));
    updatedAt.setPosition(detailsBox.getPosition().x + 25, 
                         detailsBox.getPosition().y + detailsBox.getSize().y - 30);

    while (isOpen) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                isOpen = false;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (closeButton.getGlobalBounds().contains(mousePos)) {
                    isOpen = false;
                } else if (!detailsBox.getGlobalBounds().contains(mousePos)) {
                    isOpen = false;
                }
            }
        }

        window.clear();
        drawAll();
        window.draw(overlay);
        window.draw(detailsBox);
        window.draw(headerBar);
        window.draw(weatherIcon);
        window.draw(closeButton);
        window.draw(cityName);
        window.draw(tempLarge);
        window.draw(condition);
        
        window.draw(humidity);
        window.draw(humidityValue);
        window.draw(wind);
        window.draw(windValue);
        window.draw(windDir);
        window.draw(windDirValue);
        window.draw(cloudiness);
        window.draw(cloudinessValue);
        window.draw(visibility);
        window.draw(visibilityValue);
        window.draw(pressure);
        window.draw(pressureValue);
        
        window.draw(timelineBar);
        window.draw(sunriseIcon);
        window.draw(sunrise);
        window.draw(sunsetIcon);
        window.draw(sunset);
        
        window.draw(footerDivider);
        window.draw(updatedAt);
        
        window.display();
    }
}

void WeatherDashboard::drawAll() {
    for(auto& card : cards) {
        card->Draw(window);
    }
}

void WeatherDashboard::handleResize() {
    float availableWidth = window.getSize().x - (2 * gridMargin.x);
        
    columns = static_cast<int>(availableWidth / (cardBaseSize.x + columnSpacing));
    columns = std::max(1, columns);
    
    float actualCardWidth = (availableWidth - (columns - 1)*columnSpacing) / columns;
    float cardHeight = cardBaseSize.y * (actualCardWidth / cardBaseSize.x);
    
    for(auto& card : cards) {
        card->setSize({actualCardWidth, cardHeight});
    }
    
    arrangeGrid();
}

void WeatherDashboard::updateWeather() {
    cityManager.updateWeatherForAllCities();
    refreshDashboard();
}

void WeatherDashboard::handleEvents(const sf::Event& event) {
    for (auto& card : cards) {
        card->HandleEvent(event);
    }
}

void WeatherDashboard::Update(const sf::Vector2f &mousePos) {
    for(auto& card : cards) {
        card->Update(mousePos);
    }
}

std::string windDirectionToString(int degree) {
    if (degree >= 337.5 || degree < 22.5) return "N";
    if (degree >= 22.5 && degree < 67.5) return "NE";
    if (degree >= 67.5 && degree < 112.5) return "E";
    if (degree >= 112.5 && degree < 157.5) return "SE";
    if (degree >= 157.5 && degree < 202.5) return "S";
    if (degree >= 202.5 && degree < 247.5) return "SW";
    if (degree >= 247.5 && degree < 292.5) return "W";
    return "NW";
}