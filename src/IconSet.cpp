#include "IconSet.h"

IconSet::IconSet() {}

IconSet::~IconSet() {}

bool IconSet::addIcon(const std::string &weatherCondition, const std::string &filePath) {
    Icon icon;
    if (!icon.loadFromFile(filePath)) {
        return false;
    }
    icons[weatherCondition] = std::move(icon);
    return true;
}

sf::Sprite IconSet::getIcon(const std::string &weatherCondition) const{
    auto it = icons.find(weatherCondition);
    if (it != icons.end()) {
        return it->second.getSprite();
    }
    return sf::Sprite();
}

void IconSet::clear() {
    icons.clear();
}
