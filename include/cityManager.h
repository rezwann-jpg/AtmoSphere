#ifndef CITY_MANAGER_H
#define CITY_MANAGER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>
#include "cityWeather.h"
using namespace std;

class CityManager {
private:
    std::unordered_map<std::string, std::unique_ptr<CityWeather>> cities;
    size_t maxCacheSize;
    std::vector<std::function<void()>> observers;
    
public:
    explicit CityManager(size_t cacheSize = 100);
    
    void addCity(std::unique_ptr<CityWeather> city);
    bool removeCity(const std::string& cityName);
    CityWeather* getCityByName(const std::string& cityName);
    std::vector<std::string> getAllCityNames() const;
    void clearCities();
    size_t getCityCount() const;
    void setMaxCacheSize(size_t size);

    void updateWeatherForAllCities();

    void addObserver(std::function<void()> callback);
    void notifyObservers();
};

#endif 
