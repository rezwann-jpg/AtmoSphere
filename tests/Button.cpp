#include "Button.h"

Button::Button(const sf::Vector2f &pos, const sf::Vector2f &sz, const std::string &label, const std::function<void()> &callback) : UIElement(pos, sz), onClick(callback), isPressed(false) {
    
    shape.setPosition(pos);
    shape.setSize(sz);
    UpdateVisuals();

    font.loadFromFile("assets/DMSans-Regular.ttf");
    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);

    text.setPosition(
        pos.x + (sz.x - text.getLocalBounds().width) / 2,
        pos.y + (sz.y - text.getLocalBounds().height) / 2 
    );
    
}

Button::~Button() { }

void Button::UpdateVisuals() {
    if (isPressed) {
        shape.setFillColor(sf::Color(50, 50, 200));
    }
    else if (isHovered) {
        shape.setFillColor(sf::Color(100, 100, 255));
    }
    else {
        shape.setFillColor(sf::Color::Blue);
    }
}

void Button::Draw(sf::RenderWindow &window) {
    window.draw(shape);
    window.draw(text);
}

void Button::Update(const sf::Vector2f &mousePos) {
    isHovered = shape.getGlobalBounds().contains(mousePos);
    UpdateVisuals();
}

bool Button::HandleEvent(const sf::Event &e) {
    switch (e.type) {
        case sf::Event::MouseButtonPressed:
            if (e.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(e.mouseButton.x, e.mouseButton.y);
                if (shape.getGlobalBounds().contains(mousePos)) {
                    isPressed = true;
                    UpdateVisuals();
                    return true;        
                }
            }
            break;

        case sf::Event::MouseButtonReleased:
            if (e.mouseButton.button == sf::Mouse::Left) {
                if (isPressed) {
                    isPressed = false;
                    sf::Vector2f mousePos(e.mouseButton.x, e.mouseButton.y);
                    if (shape.getGlobalBounds().contains(mousePos)) {
                        onClick();
                    }
                    UpdateVisuals();
                    return true;
                }
            }
            break;
    }

    return false;
}