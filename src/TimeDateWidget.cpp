#include "TimeDateWidget.h"

// TODO better design

TimeDateWidget::TimeDateWidget(const sf::Vector2f &pos, const sf::Vector2f &sz) : UIElement(pos, sz) {
    setupVisuals();
    initializeTimer();
}

TimeDateWidget::~TimeDateWidget() { }

void TimeDateWidget::Draw(sf::RenderWindow &window) {
    window.draw(timeText);
    window.draw(dateText);
}

void TimeDateWidget::Update(const sf::Vector2f &mousePos) {
    sf::Time elapsed = updateClock.getElapsedTime();
    if (elapsed.asSeconds() >= 1.0f) {
        updateTime();
        updateClock.restart();
    }
}

bool TimeDateWidget::HandleEvent(const sf::Event &e) {
    return false;
}

void TimeDateWidget::setTheme(const WidgetTheme& theme) {
    timeText.setFillColor(theme.primaryColor);
    timeText.setOutlineColor(theme.accentColor);
    timeText.setOutlineThickness(theme.outlineThickness);
    
    dateText.setFillColor(theme.secondaryColor);
    dateText.setOutlineColor(theme.accentColor);
    dateText.setOutlineThickness(theme.outlineThickness / 2.0f);
    
    updateTime();
}

void TimeDateWidget::setTimeFormat(const std::string& format) {
    timeFormat = format;
    updateTime();
}

void TimeDateWidget::setDateFormat(const std::string& format) {
    dateFormat = format;
    updateTime();
}

void TimeDateWidget::updateTime() {
    std::time_t now = std::time(nullptr);
    std::tm localTime = *std::localtime(&now);
    
    std::ostringstream timeStream;
    timeStream << std::put_time(&localTime, timeFormat.c_str());
    timeText.setString(timeStream.str());
    
    std::ostringstream dateStream;
    dateStream << std::put_time(&localTime, dateFormat.c_str());
    dateText.setString(dateStream.str());
    
    sf::FloatRect timeBounds = timeText.getLocalBounds();
    dateText.setPosition(position.x, position.y + timeBounds.height + 10);
}


void TimeDateWidget::setupVisuals() {
    if (!font.loadFromFile("assets/Quicksand_Book_Oblique.otf")) {
        std::cerr << "Warning: Failed to load any font, text may not display correctly\n";
    }
    
    timeText.setFont(font);
    timeText.setCharacterSize(48);
    timeText.setFillColor(sf::Color::White);
    timeText.setOutlineColor(sf::Color(255, 215, 0));
    timeText.setOutlineThickness(2);
    timeText.setPosition(position);
    
    dateText.setFont(font);
    dateText.setCharacterSize(24);
    dateText.setFillColor(sf::Color(200, 200, 200)); 
    
    timeFormat = "%H:%M";
    dateFormat = "%A, %Y-%m-%d";
    
    updateTime();
}

void TimeDateWidget::initializeTimer() {
    updateClock.restart();
}