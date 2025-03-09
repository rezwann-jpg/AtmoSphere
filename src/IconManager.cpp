#include "IconManager.h"

IconManager::IconManager() {}
IconManager::~IconManager() {}

bool IconManager::load() {
    return iconSet.addIcon("Clear", "icons/clear.png") &&
               iconSet.addIcon("Clouds", "icons/clouds.png") &&
               iconSet.addIcon("Rain", "icons/rain.png") &&
               iconSet.addIcon("Snow", "icons/snow.png") &&
               iconSet.addIcon("Thunderstorm", "icons/thunderstorm.png") &&
               iconSet.addIcon("Drizzle", "icons/drizzle.png") &&
               iconSet.addIcon("Mist", "icons/mist.png") &&
               iconSet.addIcon("Smoke", "icons/smoke.png") &&
               iconSet.addIcon("Haze", "icons/haze.png") &&
               iconSet.addIcon("Dust", "icons/dust.png") &&
               iconSet.addIcon("Fog", "icons/fog.png") &&
               iconSet.addIcon("Sand", "icons/sand.png") &&
               iconSet.addIcon("Ash", "icons/ash.png") &&
               iconSet.addIcon("Squall", "icons/squall.png") &&
               iconSet.addIcon("Tornado", "icons/tornado.png");
}

void IconManager::cleanUp() {
    iconSet.clear();
}

sf::Sprite IconManager::getIcon(const std::string& weatherCondition) const {
    return iconSet.getIcon(weatherCondition);
}

IconManager &IconManager::getInstance() {
    static IconManager instance;
    return instance;
}
