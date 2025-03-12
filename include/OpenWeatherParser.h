#ifndef OPENWEATHERPARSER_H
#define OPENWEATHERPARSER_H

#include <string>
#include "json.hpp"
#include "cityWeather.h"
#include "IWeatherParser.h"

class OpenWeatherParser : public IWeatherParser {
public:
    void parse(const std::string& jsonData, CityWeather& output) override;

private:
    void parseCityData(const nlohmann::json& jsonObj, CityWeather& output);
    void parseWeatherData(const nlohmann::json& jsonObj, DetailedWeather& weather);
    void parseTemperature(const nlohmann::json& jsonObj, DetailedWeather& weather);
    void parseAirQuality(const nlohmann::json& jsonObj, DetailedWeather& weather);
    void logError(const std::string& message) const;
};

#endif // OPENWEATHERPARSER_H