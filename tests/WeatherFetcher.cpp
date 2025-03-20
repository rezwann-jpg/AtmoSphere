#include "WeatherFetcher.h"

#include <iomanip>
#include <sstream>
#include <iostream>

WeatherFetcher::WeatherFetcher(const std::string& apiKey) : BaseFetcher(apiKey), http("http://api.openweathermap.org") {}

WeatherFetcher::~WeatherFetcher() {}

std::string WeatherFetcher::fetchData(const std::string &city) {
    QueryParams queryParams{city, m_apiKey};
    sf::Http::Request request(queryParams.buildWeatherUri(city), sf::Http::Request::Get);
    sf::Http::Response response = http.sendRequest(request);
    return (response.getStatus() == sf::Http::Response::Ok) ?
            response.getBody() :
            (std::cerr << "Http request failed with status " << response.getStatus() << std::endl, "");
}

std::string encodeURIComponent(const std::string& value) {
    std::ostringstream escaped;
    for (char c : value) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
        } else {
            escaped << '%' << std::uppercase << std::hex << (int)c;
        }
    }
    return escaped.str();
}

std::string WeatherFetcher::QueryParams::toUri() const {
    return "/data/2.5/weather?q=" + encodeURIComponent(m_city) + "&appid=" + m_apiKey + "&mode=" + m_mode + "&units=" + m_units;
}

std::string WeatherFetcher::QueryParams::buildWeatherUri(const std::string &city) const {
    return QueryParams{city, m_apiKey}.toUri();
}
