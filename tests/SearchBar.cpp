#include "SearchBar.h"

// TODO error handling
// TODO better ui design
// TODO better search suggestion design

SearchBar::SearchBar(const sf::Vector2f &pos, const sf::Vector2f &sz, const std::function<void(const std::string &)> &submitCallback) : UIElement(pos, sz), isFocused(false), onSubmit(submitCallback), selectedSuggestion(-1) {
    
    shape.setPosition(pos);
    shape.setSize(sz);
    shape.setFillColor(sf::Color(240, 240, 250, 225));
    shape.setOutlineThickness(1.5f);
    shape.setOutlineColor(sf::Color(100, 100, 220, 200));

    roundedShape.setPosition(pos);
    roundedShape.setSize(sz);
    roundedShape.setRadius(8);
    roundedShape.setFillColor(sf::Color(240, 240, 250, 225));
    
    font.loadFromFile("assets/DMSans-Regular.ttf");
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(pos.x + 5, pos.y + 5);

    placeholder.setFont(font);
    placeholder.setString("Search for a city...");
    placeholder.setCharacterSize(18);
    placeholder.setFillColor(sf::Color(150, 150, 170, 180));
    placeholder.setPosition(pos.x + 30, pos.y + (sz.y - 18) / 2);

    suggestionBox.setPosition(pos.x, pos.y + sz.y + 2);
    suggestionBox.setFillColor(sf::Color(250, 250, 255, 250));
    suggestionBox.setOutlineThickness(1);
    suggestionBox.setOutlineColor(sf::Color(180, 180, 220));

    roundedSuggestionBox.setPosition(pos);
    roundedSuggestionBox.setSize(sf::Vector2f(sz.x, 0));
    roundedSuggestionBox.setPosition(pos.x, pos.y + sz.y + 2);
    roundedSuggestionBox.setFillColor(sf::Color(250, 250, 255, 250));

    LoadCitiesOntoTrie();
}

SearchBar::~SearchBar() { }

void SearchBar::Draw(sf::RenderWindow &window) {
    // window.draw(shape);
    window.draw(roundedShape);
    
    if (input.empty() && !isFocused) {
        window.draw(placeholder);
    } else {
        text.setString(input + (isFocused && fmod(clock.getElapsedTime().asSeconds(), 1.0f) < 0.5f ? "|" : ""));
        window.draw(text);
    }

    if (!suggestions.empty()) {
        // window.draw(suggestionBox);
        window.draw(roundedSuggestionBox);
        
        if (selectedSuggestion >= 0 && selectedSuggestion < static_cast<int>(suggestions.size())) {
            sf::RectangleShape highlight;
            highlight.setPosition(suggestionBox.getPosition().x + 2, 
                suggestionBox.getPosition().y + selectedSuggestion * (text.getCharacterSize() + 10) + 2);
            highlight.setSize(sf::Vector2f(suggestionBox.getSize().x - 4, text.getCharacterSize() + 6));
            highlight.setFillColor(sf::Color(220, 220, 255));
            window.draw(highlight);
        }
        
        for (const auto& suggestionText : suggestionTexts) {
            window.draw(suggestionText);
        }
    }
}

void SearchBar::Update(const sf::Vector2f &mousePos) {
    isHovered = shape.getGlobalBounds().contains(mousePos);
    
    if (isHovered) {
        sf::Color hoverColor = sf::Color(120, 140, 255, 220);
        shape.setOutlineColor(hoverColor);
        roundedShape.setOutlineColor(hoverColor);
    } else {
        sf::Color normalColor = isFocused ? sf::Color(80, 120, 255, 220) : sf::Color(100, 100, 220, 200);
        shape.setOutlineColor(normalColor);
        roundedShape.setOutlineColor(normalColor);
    }

    for (size_t i = 0; i < suggestions.size(); i++) {
        bool isHoveredSuggestion = suggestionTexts[i].getGlobalBounds().contains(mousePos);
        bool isSelectedSuggestion = static_cast<int>(i) == selectedSuggestion;
        
        if (isHoveredSuggestion || isSelectedSuggestion) {
            suggestionTexts[i].setFillColor(sf::Color(50, 80, 230));
            suggestionTexts[i].setStyle(sf::Text::Bold);
        } else {
            suggestionTexts[i].setFillColor(sf::Color(60, 60, 80));
            suggestionTexts[i].setStyle(sf::Text::Regular);
        }
    }
}

bool SearchBar::HandleEvent(const sf::Event &e) {
    switch (e.type) {
        case sf::Event::MouseButtonPressed: {
            sf::Vector2f mousePos(e.mouseButton.x, e.mouseButton.y);

            if (shape.getGlobalBounds().contains(mousePos)) {
                isFocused = true;

                if (!input.empty()) {
                    UpdateSuggestions();
                }
            }
            else if (suggestionBox.getGlobalBounds().contains(mousePos)) {
                for (size_t i = 0; i < suggestionTexts.size(); i++) {
                    if (suggestionTexts[i].getGlobalBounds().contains(mousePos)) {
                        input = suggestions[i];
                        onSubmit(input);
                        input.clear();
                        ClearSuggestions();
                        return true;
                    }
                }
            }
            else {
                isFocused = false;

                ClearSuggestions();
            }
            return true;
        }

        case sf::Event::KeyPressed:
            if (isFocused) {
                if (e.key.code == sf::Keyboard::Escape) {
                    isFocused = false;
                    ClearSuggestions();
                    return true;
                }

                if (!suggestions.empty()) {
                    if (e.key.code == sf::Keyboard::Down) {
                        selectedSuggestion = (selectedSuggestion + 1) % suggestions.size();
                        UpdateSuggestionHighlight();
                        return true;
                    }
                    else if (e.key.code == sf::Keyboard::Up) {
                        selectedSuggestion = (selectedSuggestion - 1 + suggestions.size()) % suggestions.size();
                        UpdateSuggestionHighlight();
                        return true;
                    }
                    else if (e.key.code == sf::Keyboard::Enter || e.key.code == sf::Keyboard::Tab) {
                        if (selectedSuggestion != -1) {
                            input = suggestions[selectedSuggestion];
                            if (e.key.code == sf::Keyboard::Enter) {
                                onSubmit(input);
                                input.clear();
                            }
                            ClearSuggestions();
                            return true;
                        }
                    }
                }
                
                if (e.key.code == sf::Keyboard::Enter && !input.empty()) {
                    onSubmit(input);
                    input.clear();
                    ClearSuggestions();
                    return true;
                }
            }
            break;

        case sf::Event::TextEntered:
            if (isFocused) {
                if (e.text.unicode == '\b' && !input.empty()) {
                    input.pop_back();
                    UpdateSuggestions();
                }
                else if (e.text.unicode == '\r' || e.text.unicode == '\n') {
                    
                }
                else if (e.text.unicode >= 32 && e.text.unicode < 128) {
                    input += static_cast<char>(e.text.unicode);
                    UpdateSuggestions();
                }
                selectedSuggestion = -1;
                return true;
            }
            break;
    }
    return false;
}

void SearchBar::LoadCitiesOntoTrie() {
    std::ifstream iFile;
    iFile.open("assets/cities.txt");

    if (!iFile.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    std::string city;
    while (std::getline(iFile, city)) {
        trie.Insert(city);
    }
    // std::cout << "Loaded cities onto trie\n";
}

void SearchBar::UpdateSuggestions() {
    suggestions.clear();
    suggestionTexts.clear();
    
    if (!input.empty()) {
        suggestions = trie.SearchSuggestions(input);
        if (suggestions.size() > 5) {
            suggestions.resize(5);
        }
    }

    if (suggestions.empty()) {
        roundedSuggestionBox.setSize(sf::Vector2f(0, 0));
        return;
    }

    float suggestionHeight = text.getCharacterSize() + 10;
    float boxHeight = suggestions.size() * suggestionHeight;
    
    suggestionBox.setSize(sf::Vector2f(shape.getSize().x, boxHeight));
    roundedSuggestionBox.setSize(sf::Vector2f(shape.getSize().x, boxHeight));

    for (size_t i = 0; i < suggestions.size(); i++) {
        sf::Text suggestionText;
        suggestionText.setFont(font);
        suggestionText.setCharacterSize(18);
        suggestionText.setFillColor(sf::Color(60, 60, 80));
        suggestionText.setString(suggestions[i]);
        
        std::string matchedPart = suggestions[i].substr(0, input.size());
        std::string restPart = suggestions[i].substr(input.size());
        
        suggestionText.setPosition(
            suggestionBox.getPosition().x + 30,
            suggestionBox.getPosition().y + i * suggestionHeight + 5
        );
        
        suggestionTexts.push_back(suggestionText);
    }
}

void SearchBar::UpdateSuggestionHighlight() {
    for (size_t i = 0; i < suggestions.size(); i++) {
        if (static_cast<int>(i) == selectedSuggestion) {
            suggestionTexts[i].setFillColor(sf::Color(50, 80, 230));
            suggestionTexts[i].setStyle(sf::Text::Bold);
        } else {
            suggestionTexts[i].setFillColor(sf::Color(60, 60, 80));
            suggestionTexts[i].setStyle(sf::Text::Regular);
        }
    }
}

void SearchBar::ClearSuggestions() {
    suggestions.clear();
    suggestionTexts.clear();
    selectedSuggestion = -1;
}