#include "SearchBar.h"

SearchBar::SearchBar(const sf::Vector2f &pos, const sf::Vector2f &sz, const std::function<void(const std::string &)> &submitCallback) : UIElement(pos, sz), isFocused(false), onSubmit(submitCallback) {
    
    shape.setPosition(pos);
    shape.setSize(sz);
    shape.setFillColor(sf::Color::White);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Blue);

    font.loadFromFile("assets/DMSans-Regular.ttf");
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(pos.x + 5, pos.y + 5);
}

SearchBar::~SearchBar() { }

void SearchBar::Draw(sf::RenderWindow &window) {
    window.draw(shape);
    text.setString(input + (isFocused ? "|" : ""));
    window.draw(text);
}

void SearchBar::Update(const sf::Vector2f &mousePos) {
    isHovered = shape.getGlobalBounds().contains(mousePos);
    if (isHovered) {
        shape.setOutlineColor(sf::Color::Cyan);
    }
    else {
        shape.setOutlineColor(sf::Color::Blue);
    }
}

bool SearchBar::HandleEvent(const sf::Event &e) {
    switch (e.type) {
        case sf::Event::MouseButtonPressed:
            isFocused = shape.getGlobalBounds().contains(
                sf::Vector2f(e.mouseButton.x, e.mouseButton.y)
            );
            return isFocused;
            break;

        case sf::Event::TextEntered:
            if (isFocused) {
                if (e.text.unicode == '\b' && !input.empty()) {
                    input.pop_back();
                }
                else if (e.text.unicode == '\r' || e.text.unicode == '\n') {
                    if (!input.empty()) {
                        onSubmit(input);
                        input.clear();
                    }
                }
                else if (e.text.unicode >= 32 && e.text.unicode < 128) {
                    input += static_cast<char>(e.text.unicode);
                }
                return true;
            }
            break;
    }
    return false;
}