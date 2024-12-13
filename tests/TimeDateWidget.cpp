#include "TimeDateWidget.h"

TimeDateWidget::TimeDateWidget(const sf::Vector2f &pos, const sf::Vector2f &sz) : UIElement(pos, sz) {

    if (!font.loadFromFile("assets/alagard.ttf")) {
        throw std::runtime_error("Failed to load font\n");
    }

    timeText.setFont(font);
    timeText.setCharacterSize(48);
    timeText.setFillColor(sf::Color::White);
    timeText.setOutlineColor(sf::Color::Yellow);
    timeText.setOutlineThickness(2);
    timeText.setPosition(position);

    dateText.setFont(font);
    dateText.setCharacterSize(24);
    dateText.setFillColor(sf::Color::Black);
    dateText.setPosition(position.x, position.y + 60);

    updateTime();
}

TimeDateWidget::~TimeDateWidget() { }

void TimeDateWidget::Draw(sf::RenderWindow &window) {
    window.draw(timeText);
    window.draw(dateText);
}

void TimeDateWidget::Update(const sf::Vector2f &mousePos) {
    updateTime();
}

bool TimeDateWidget::HandleEvent(const sf::Event &e) {
    return false;
}

void TimeDateWidget::updateTime() {
    std::time_t now = std::time(nullptr);
    std::tm localTime = *std::localtime(&now);

    std::ostringstream timeStream;
    timeStream << std::put_time(&localTime, "%H:%M:%S");
    timeText.setString(timeStream.str());

    std::ostringstream dateStream;
    dateStream << std::put_time(&localTime, "%A, %Y-%m-%d");
    dateText.setString(dateStream.str());
}
