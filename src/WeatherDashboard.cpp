#include "WeatherDashboard.h"

WeatherDashboard::WeatherDashboard(const sf::Vector2f& pos, CityManager& cm, sf::RenderWindow& win) : gridMargin(pos), cityManager(cm), window(win) {
    if(!font.loadFromFile("assets/DMSans-Regular.ttf")) {
        throw WeatherException("Font loading failed");
    }
    
    cityManager.addObserver([this]() { refreshDashboard(); });

    refreshDashboard();
}

WeatherDashboard::~WeatherDashboard() {}

void WeatherDashboard::refreshDashboard() {
    cards.clear();
        
    auto cityNames = cityManager.getAllCityNames();
    for(const auto& name : cityNames) {
        auto* city = cityManager.getCityByName(name);
        if(!city) continue;
        
        auto card = std::make_unique<WeatherCard>(
            sf::Vector2f(0, 0),
            cardBaseSize,
            city,
            font,
            [this](CityWeather* city){ showDetailedView(city); }
        );
        
        cards.push_back(std::move(card));
    }
    
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
    // TODO: popup mode
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

void WeatherDashboard::Update() {
    for(auto& card : cards) {
        card->Update();
    }
}
