#ifndef IWEATHERPARSER_H
#define IWEATHERPARSER_H

#include "cityWeather.h"
#include <string>
#include "json.hpp"

class IWeatherParser {
public:
    virtual ~IWeatherParser() = default;
    virtual void parse(const std::string& jsonData, CityWeather& output) = 0;
};

#endif // IWEATHERPARSER_H
