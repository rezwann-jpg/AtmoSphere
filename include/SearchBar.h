#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#pragma once

#include "UIElement.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

class SearchBar : public UIElement {
public:
    SearchBar(const sf::Vector2f& pos, const sf::Vector2f& sz, const std::function<void(const std::string&)>& submitCallback);
    ~SearchBar();

    // TODO no arg constructor

    void Draw(sf::RenderWindow& window) override;
    void Update(const sf::Vector2f& mousePos) override;
    bool HandleEvent(const sf::Event& e) override;

private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;
    std::string input;
    bool isFocused;
    std::function<void(const std::string&)> onSubmit;

};

#endif