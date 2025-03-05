#ifndef WEATHER_OBSERVER_HPP
#define WEATHER_OBSERVER_HPP

#include <string>
#include "detailedWeather.h"

using namespace std;

class WeatherObserver {
public:
    virtual ~WeatherObserver() = default;
    virtual void onWeatherUpdate(const string& cityName, const DetailedWeather& weather) = 0;
};

#endif 
