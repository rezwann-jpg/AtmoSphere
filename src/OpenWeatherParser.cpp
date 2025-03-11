#include "OpenWeatherParser.h"
#include <iostream>

void OpenWeatherParser::parse(const std::string& jsonData, CityWeather& output) {
    try {
        nlohmann::json jsonObj = nlohmann::json::parse(jsonData);

        parseCityData(jsonObj, output);
        DetailedWeather weather;
        parseWeatherData(jsonObj, weather);
        parseTemperature(jsonObj, weather);
        output.updateWeather(weather);
    } catch (const std::exception& e) {
        logError("Error parsing weather data: " + std::string(e.what()));
    }
}

void OpenWeatherParser::parseCityData(const nlohmann::json& jsonObj, CityWeather& output) {
    try {
        if (jsonObj.contains("name")) output.setCityName(jsonObj["name"]);
        if (jsonObj.contains("sys") && jsonObj["sys"].contains("country"))
            output.setCountryCode(jsonObj["sys"]["country"]);
        if (jsonObj.contains("coord")) {
            if (jsonObj["coord"].contains("lat")) output.setLatitude(jsonObj["coord"]["lat"]);
            if (jsonObj["coord"].contains("lon")) output.setLongitude(jsonObj["coord"]["lon"]);
        }
        if (jsonObj.contains("timezone")) output.setTimezone(jsonObj["timezone"]);
    } catch (const std::exception& e) {
        logError("Error parsing city data: " + std::string(e.what()));
    }
}

void OpenWeatherParser::parseWeatherData(const nlohmann::json& jsonObj, DetailedWeather& weather) {
    try {
        if (jsonObj.contains("wind")) {
            if (jsonObj["wind"].contains("speed")) weather.setWindSpeed(jsonObj["wind"]["speed"]);
            if (jsonObj["wind"].contains("deg")) weather.setWindDegree(jsonObj["wind"]["deg"]);
        }
        if (jsonObj.contains("visibility")) weather.setVisibility(jsonObj["visibility"]);
        if (jsonObj.contains("clouds") && jsonObj["clouds"].contains("all"))
            weather.setCloudiness(jsonObj["clouds"]["all"]);
        if (jsonObj.contains("sys")) {
            if (jsonObj["sys"].contains("sunrise")) weather.setSunrise(jsonObj["sys"]["sunrise"]);
            if (jsonObj["sys"].contains("sunset")) weather.setSunset(jsonObj["sys"]["sunset"]);
        }
    } catch (const std::exception& e) {
        logError("Error parsing weather data: " + std::string(e.what()));
    }
}

void OpenWeatherParser::parseTemperature(const nlohmann::json& jsonObj, DetailedWeather& weather) {
    try {
        if (jsonObj.contains("main")) {
            if (jsonObj["main"].contains("temp")) weather.setTemperature(jsonObj["main"]["temp"]);
            if (jsonObj["main"].contains("feels_like")) weather.setFeelsLike(jsonObj["main"]["feels_like"]);
            if (jsonObj["main"].contains("humidity")) weather.setHumidity(jsonObj["main"]["humidity"]);
            if (jsonObj["main"].contains("pressure")) weather.setPressure(jsonObj["main"]["pressure"]);
        }
    } catch (const std::exception& e) {
        logError("Error parsing temperature data: " + std::string(e.what()));
    }
}

void OpenWeatherParser::logError(const std::string& message) const {
    std::cerr << "Error: " << message << std::endl;
}