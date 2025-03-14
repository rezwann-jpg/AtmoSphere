#include "IconSet.h"
#include <iostream>

IconSet::IconSet() {}

IconSet::~IconSet() {}

bool IconSet::addIcon(const std::string &weatherCondition, const std::string &filePath) {
    Icon *icon = new Icon();
    if (!icon->loadFromFile(filePath)) {
        std::cerr << "Failed to load icon for " << weatherCondition << " from: " << filePath << std::endl;
        return false;
    }
    icons[weatherCondition] = std::move(icon);
    std::cout << "Loaded icon for " << weatherCondition << " from: " << filePath << std::endl;
    return true;
}

sf::Sprite& IconSet::getIcon(const std::string &weatherCondition) {
    static Icon defaultIcon;
    static bool defaultInitialized = false;
    
    if (!defaultInitialized) {
        sf::Image img;
        img.create(32, 32, sf::Color(200, 200, 200, 255));
        defaultIcon.getTexture().loadFromImage(img);
        defaultIcon.getSprite().setTexture(defaultIcon.getTexture());
        defaultInitialized = true;
    }
    
    auto it = icons.find(weatherCondition);
    if (it != icons.end()) {
        return it->second->getSprite();
    }
    
    std::cerr << "Weather icon not found for: " << weatherCondition << std::endl;
    return defaultIcon.getSprite();
}

void IconSet::clear() {
    icons.clear();
}
