#ifndef WEATHERFETCHER_H
#define WEATHERFETCHER_H

#pragma once

#include "BaseFetcher.h"
#include <SFML/Network.hpp>

class WeatherFetcher : public BaseFetcher {
public:
    WeatherFetcher(const std::string& apiKey);
    ~WeatherFetcher();

    std::string fetchData(const std::string& city) override;

private:
    sf::Http http;

    struct QueryParams {
        std::string m_city;
        std::string m_apiKey;
        std::string m_mode = "json";
        std::string m_units = "standerd";

        std::string toUri() const;
        std::string buildWeatherUri(const std::string& city) const;
    };
};

#endif