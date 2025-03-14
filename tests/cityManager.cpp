#include "cityManager.h"
#include "WeatherService.h"

CityManager::CityManager(size_t cacheSize) : maxCacheSize(cacheSize) {}

void CityManager::addCity(std::unique_ptr<CityWeather> city) {
    if (cities.size() >= maxCacheSize) {
        cities.erase(cities.begin());
    }
    std::string cityName = city->getCityName();
    cities[cityName] = std::move(city);
    notifyObservers();
}

bool CityManager::removeCity(const std::string& cityName) {
    return cities.erase(cityName) > 0;
}

CityWeather* CityManager::getCityByName(const std::string& cityName) {
    auto it = cities.find(cityName);
    return it != cities.end() ? it->second.get() : nullptr;
}

std::vector<std::string> CityManager::getAllCityNames() const {
    std::vector<std::string> names;
    for (const auto& pair : cities) {
        names.push_back(pair.first);
    }
    return names;
}

void CityManager::clearCities() {
    cities.clear();
}

size_t CityManager::getCityCount() const {
    return cities.size();
}

void CityManager::setMaxCacheSize(size_t size) {
    maxCacheSize = size;
    while (cities.size() > maxCacheSize) {
        cities.erase(cities.begin());
    }
}

void CityManager::updateWeatherForAllCities() {
    WeatherService ws("99cf5d3f3e51411bb01ed89e384a01a4");

    for (const auto& cityName : getAllCityNames()) {
        CityWeather updatedWeather;
        updatedWeather = ws.getWeatherForCity(cityName);

        CityWeather* city = getCityByName(cityName);
        if (city) {
            city->updateWeather(updatedWeather.getWeather());
        }
    }
}

void CityManager::addObserver(std::function<void()> callback) {
    observers.push_back(callback);
}

void CityManager::notifyObservers() {
    for (auto& observer : observers) {
        observer();
    }
}