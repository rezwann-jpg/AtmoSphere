#include "SearchBar.h"

// TODO error handling
// TODO better ui design
// TODO better search suggestion design

SearchBar::SearchBar(const sf::Vector2f &pos, const sf::Vector2f &sz, const std::function<void(const std::string &)> &submitCallback) : UIElement(pos, sz), isFocused(false), onSubmit(submitCallback), selectedSuggestion(-1) {
    
    shape.setPosition(pos);
    shape.setSize(sz);
    shape.setFillColor(sf::Color(50, 50, 200, 100));
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Blue);

    font.loadFromFile("assets/DMSans-Regular.ttf");
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(pos.x + 5, pos.y + 5);

    suggestionBox.setPosition(pos.x, pos.y + sz.y);

    LoadCitiesOntoTrie();
}

SearchBar::~SearchBar() { }

void SearchBar::Draw(sf::RenderWindow &window) {
    window.draw(shape);
    text.setString(input + (isFocused ? "|" : ""));
    window.draw(text);

    if (!suggestions.empty()) {
        window.draw(suggestionBox);
        for (const auto& suggestionText : suggestionTexts) {
            window.draw(suggestionText);
        }
    }
}

void SearchBar::Update(const sf::Vector2f &mousePos) {
    isHovered = shape.getGlobalBounds().contains(mousePos);
    if (isHovered) {
        shape.setOutlineColor(sf::Color::Cyan);
    }
    else {
        shape.setOutlineColor(sf::Color::Blue);
    }

    for (size_t i = 0; i < suggestions.size(); i++) {
        suggestionTexts[i].setFillColor(suggestionTexts[i].getGlobalBounds().contains(mousePos) ? sf::Color::Blue : sf::Color::Black);
    }
}

bool SearchBar::HandleEvent(const sf::Event &e) {
    switch (e.type) {
        case sf::Event::MouseButtonPressed: {
            sf::Vector2f mousePos(e.mouseButton.x, e.mouseButton.y);

            if (shape.getGlobalBounds().contains(mousePos)) {
                isFocused = true;
            }
            else if (suggestionBox.getGlobalBounds().contains(mousePos)) {
                for (size_t i = 0; i < suggestionTexts.size(); i++) {
                    if (suggestionTexts[i].getGlobalBounds().contains(mousePos)) {
                        input = suggestions[i];
                        onSubmit(input);
                        input.clear();
                        suggestions.clear();
                        suggestionTexts.clear();
                        return true;
                    }
                }
            }
            else {
                isFocused = false;
            }
            return true;
        }

        case sf::Event::KeyPressed:
            if (isFocused && !suggestions.empty()) {
                if (e.key.code == sf::Keyboard::Down) {
                    selectedSuggestion = (selectedSuggestion + 1) % suggestions.size();
                    UpdateSuggestionHighlight();
                }
                else if (e.key.code == sf::Keyboard::Up) {
                    selectedSuggestion = (selectedSuggestion - 1 + suggestions.size()) % suggestions.size();
                    UpdateSuggestionHighlight();
                }
                else if (e.key.code == sf::Keyboard::Enter) {
                    if (selectedSuggestion != -1) {
                        input = suggestions[selectedSuggestion];
                        onSubmit(input);
                        input.clear();
                        suggestions.clear();
                        suggestionTexts.clear();
                    }
                }
                return true;
            }
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
                        suggestions.clear();
                        suggestionTexts.clear();
                    }
                }
                else if (e.text.unicode >= 32 && e.text.unicode < 128) {
                    input += static_cast<char>(e.text.unicode);
                }
                UpdateSuggestions();
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
    if (!input.empty()) {
        suggestions = trie.SearchSuggestions(input);
        if (suggestions.size() > 5) {
            suggestions.resize(5);
        }
    }
    else {
        suggestions.clear();
    }

    suggestionTexts.clear();
    float suggestionHeight = text.getCharacterSize() + 5;
    suggestionBox.setSize(sf::Vector2f(shape.getSize().x, suggestions.size() * suggestionHeight));

    for (size_t i = 0; i < suggestions.size(); i++) {
        sf::Text suggestionText;
        suggestionText.setFont(font);
        suggestionText.setCharacterSize(20);
        suggestionText.setFillColor(i == selectedSuggestion ? sf::Color::Blue : sf::Color::Black);
        suggestionText.setString(suggestions[i]);
        suggestionText.setPosition(suggestionBox.getPosition().x, suggestionBox.getPosition().y + i * suggestionHeight);
        suggestionTexts.push_back(suggestionText);
    }
}

void SearchBar::UpdateSuggestionHighlight() {
    for (size_t i = 0; i < suggestions.size(); i++) {
        if (static_cast<int>(i) == selectedSuggestion) {
            suggestionTexts[i].setFillColor(sf::Color::Blue);
        }
        else {
            suggestionTexts[i].setFillColor(sf::Color::Black);
        }
    }
}