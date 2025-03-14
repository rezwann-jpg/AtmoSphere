#include "WeatherService.h"
#include <iostream>

WeatherService::WeatherService(const std::string& apiKey) {
    fetcher = std::make_unique<WeatherFetcher>(apiKey);
    parser = std::make_unique<OpenWeatherParser>();
}

WeatherService::~WeatherService() {}

CityWeather WeatherService::getWeatherForCity(const std::string& city) {
    std::string weatherData = fetcher->fetchData(city);
    
    if (weatherData.empty()) {
        std::cerr << "Failed to fetch weather data for: " << city << std::endl;
        return CityWeather();
    }

    CityWeather cityWeather;
    parser->parse(weatherData, cityWeather);
    
    return cityWeather;
}
