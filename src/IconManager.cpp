#include "IconManager.h"

IconManager::IconManager() {}
IconManager::~IconManager() {}

bool IconManager::load() {
    if (isLoaded) return true;

    bool success = iconSet.addIcon("Clear", "assets/clear.png") &&
               iconSet.addIcon("Clouds", "assets/clouds.png") &&
               iconSet.addIcon("Rain", "assets/rain.png") &&
               iconSet.addIcon("Snow", "assets/snow.png") &&
               iconSet.addIcon("Thunderstorm", "assets/thunderstorm.png") &&
               iconSet.addIcon("Drizzle", "assets/drizzle.png") &&
               iconSet.addIcon("Mist", "assets/mist.png") &&
               iconSet.addIcon("Smoke", "assets/smoke.png") &&
               iconSet.addIcon("Haze", "assets/haze.png") &&
               iconSet.addIcon("Dust", "assets/dusty.png") &&
               iconSet.addIcon("Fog", "assets/fog.png") &&
               iconSet.addIcon("Sand", "assets/sand.png") &&
               iconSet.addIcon("Ash", "assets/ash.png") &&
               iconSet.addIcon("Squall", "assets/squall.png") &&
               iconSet.addIcon("Tornado", "assets/tornado.png") &&
               iconSet.addIcon("Sunrise", "assets/sunrise.png") &&
               iconSet.addIcon("Sunset", "assets/sunset.png");

    isLoaded = success;
    return success;
}

void IconManager::cleanUp() {
    iconSet.clear();
    isLoaded = false;
}

sf::Sprite& IconManager::getIcon(const std::string& weatherCondition) {
    if (!isLoaded) {
        load();
    }
    return iconSet.getIcon(weatherCondition);
}

IconManager &IconManager::getInstance() {
    static IconManager instance;
    return instance;
}
