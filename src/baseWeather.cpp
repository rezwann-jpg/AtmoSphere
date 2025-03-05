
#include "baseWeather.h"

using namespace std;
BaseWeather::BaseWeather() : temperature(0), feelsLike(0), humidity(0), pressure(0) {}

double BaseWeather::getTemperature() const { return temperature; }
double BaseWeather::getFeelsLike() const { return feelsLike; }
int BaseWeather::getHumidity() const { return humidity; }
int BaseWeather::getPressure() const { return pressure; }
const string& BaseWeather::getWeatherMain() const { return weatherMain; }
const string& BaseWeather::getWeatherDescription() const { return weatherDescription; }

void BaseWeather::setTemperature(double temp) {
    double celsius = temp - 273.15;
    if (celsius < -100 || celsius > 100) {
        throw WeatherException("Temperature out of realistic range");
    }
    temperature = celsius;
}

void BaseWeather::setFeelsLike(double feels) {
    double celsius = feels - 273.15;
    if (celsius < -100 || celsius > 100) {
        throw WeatherException("Feels-like temperature out of realistic range");
    }
    feelsLike = celsius;
}

void BaseWeather::setHumidity(int h) {
    if (h < 0 || h > 100) {
        throw WeatherException("Humidity must be between 0 and 100");
    }
    humidity = h;
}

void BaseWeather::setPressure(int p) {
    if (p < 800 || p > 1200) {
        throw WeatherException("Pressure out of realistic range");
    }
    pressure = p;
}

void BaseWeather::setWeatherMain(const string& main) { weatherMain = main; }
void BaseWeather::setWeatherDescription(const string& desc) { weatherDescription = desc; }
