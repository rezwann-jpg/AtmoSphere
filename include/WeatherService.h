#ifndef WEATHERSERVICE_H
#define WEATHERSERVICE_H

#pragma once

#include "WeatherFetcher.h"
#include "OpenWeatherParser.h"
#include "CityWeather.h"
#include <memory>

class WeatherService {
public:
    explicit WeatherService(const std::string& apiKey);
    ~WeatherService();

    CityWeather getWeatherForCity(const std::string& city);

private:
    std::unique_ptr<WeatherFetcher> fetcher;
    std::unique_ptr<OpenWeatherParser> parser;
};

#endif // WEATHERSERVICE_H
