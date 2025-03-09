#include "cityManager.h"
#include <iostream>
using namespace std;

CityWeather::CityWeather() : latitude(0), longitude(0), timezone(0) {}

void CityWeather::addObserver(const std::shared_ptr<WeatherObserver>& observer) {
    observers.push_back(observer);
}

void CityWeather::notifyObservers() {
    // Remove expired observers
    observers.erase(std::remove_if(observers.begin(), observers.end(),
        [](const std::weak_ptr<WeatherObserver>& wo) { return wo.expired(); }),
        observers.end());
    // Notify active observers
     for (const auto& wo : observers) {
        if (auto observer = wo.lock()) {
            observer->onWeatherUpdate(cityName, weather);
        }
    }
}

std::string CityWeather::getCityName() const { return cityName; }
std::string CityWeather::getCountryCode() const { return countryCode; }
double CityWeather::getLatitude() const { return latitude; }
double CityWeather::getLongitude() const { return longitude; }
int CityWeather::getTimezone() const { return timezone; }
const DetailedWeather& CityWeather::getWeather() const { return weather; }
DetailedWeather& CityWeather::getWeatherRef() { return weather; }

void CityWeather::setCityName(const std::string& name) {
    if (name.empty()) {
        throw WeatherException("City name cannot be empty");
    }
    cityName = name;
}

void CityWeather::setCountryCode(const std::string& code) {
    if (code.length() != 2) {
        throw WeatherException("Country code must be 2 characters");
    }
    countryCode = code;
}

void CityWeather::setLatitude(double lat) {
    if (lat < -90 || lat > 90) {
        throw WeatherException("Latitude must be between -90 and 90");
    }
    latitude = lat;
}

void CityWeather::setLongitude(double lon) {
    if (lon < -180 || lon > 180) {
        throw WeatherException("Longitude must be between -180 and 180");
    }
    longitude = lon;
}

void CityWeather::setTimezone(int tz) {
    if (tz < -43200 || tz > 43200) {
        throw WeatherException("Timezone offset out of range");
    }
    timezone = tz;
}

void CityWeather::updateWeather(const DetailedWeather& newWeather) {
    weather = newWeather;
    notifyObservers();
}

void CityWeather::display() const {
    cout << "City: " << cityName << "\n"
              << "Temperature: " << weather.getTemperature() << "°C\n"
              << "Feels Like: " << weather.getFeelsLike() << "°C\n"
              << "Humidity: " << weather.getHumidity() << "%\n"
              << "Pressure: " << weather.getPressure() << " hPa\n"
              << "Weather: " << weather.getWeatherMain() << " - " << weather.getWeatherDescription() << "\n"
              << "Wind Speed: " << weather.getWindSpeed() << " m/s\n"
              << "Wind Degree: " << weather.getWindDegree() << "\n"
              << "Visibility: " << weather.getVisibility() << " m\n"
              << "Cloudiness: " << weather.getCloudiness() << "%\n";
}
