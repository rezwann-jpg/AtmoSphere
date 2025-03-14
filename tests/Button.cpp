#include "Button.h"

Button::Button(const sf::Vector2f &pos, const sf::Vector2f &sz, const std::string &label, const std::function<void()> &callback) : UIElement(pos, sz), onClick(callback), isPressed(false), isActive(true) {
    shape.setPosition(pos);
    shape.setSize(sz);
    shape.setRadius(20);

    font.loadFromFile("assets/DMSans-Regular.ttf");
    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    
    UpdateVisuals();

    CenterText();
}

Button::~Button() { }

void Button::CenterText() {
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        position.x + (size.x - textBounds.width) / 2,
        position.y + (size.y - textBounds.height) / 2 - textBounds.top
    );
}

void Button::UpdateVisuals() {
    if (!isActive) {
        shape.setFillColor(sf::Color(120, 120, 170));
        text.setFillColor(sf::Color(200, 200, 220));
    }
    else if (isPressed) {
        shape.setFillColor(sf::Color(40, 40, 180));
        shape.setPosition(position.x + 1, position.y + 1);
        
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(
            position.x + (size.x - textBounds.width) / 2 + 1,
            position.y + (size.y - textBounds.height) / 2 - textBounds.top + 1
        );
    }
    else if (isHovered) {
        shape.setFillColor(sf::Color(80, 80, 230));
        shape.setPosition(position);
        
        CenterText();
    }
    else {
        shape.setFillColor(sf::Color(60, 60, 220));
        shape.setPosition(position);
        
        CenterText();
    }
}

void Button::SetLabel(const std::string &label) {
    text.setString(label);
    CenterText();
}

void Button::SetActive(bool active) {
    isActive = active;
    UpdateVisuals();
}

bool Button::IsActive() const {
    return isActive;
}

void Button::Draw(sf::RenderWindow &window) {
    window.draw(shape);
    window.draw(text);;
}

void Button::Update(const sf::Vector2f &mousePos) {
    bool wasHovered = isHovered;
    isHovered = shape.getGlobalBounds().contains(mousePos) && isActive;
    
    if (wasHovered != isHovered || isPressed) {
        UpdateVisuals();
    }
}

bool Button::HandleEvent(const sf::Event &e) {
    if (!isActive) return false;

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

        case sf::Event::MouseMoved:
            if (isPressed) {
                sf::Vector2f mousePos(e.mouseMove.x, e.mouseMove.y);
                isHovered = shape.getGlobalBounds().contains(mousePos);
                UpdateVisuals();
                return true;
            }
            break;
    }

    return false;
}

void Button::SetPosition(const sf::Vector2f &pos) {
    position = pos;
    shape.setPosition(pos);
    CenterText();
    UpdateVisuals();
}

void Button::SetSize(const sf::Vector2f &sz) {
    size = sz;
    shape.setSize(sz);
    CenterText();
    UpdateVisuals();
}

void Button::SetColors(const sf::Color &normal, const sf::Color &hover, const sf::Color &pressed) {
    normalColor = normal;
    hoverColor = hover;
    pressedColor = pressed;
    UpdateVisuals();
}