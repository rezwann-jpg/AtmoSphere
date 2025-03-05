#ifndef FILE_WEATHER_OBSERVER_HPP
#define FILE_WEATHER_OBSERVER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include "weatherObserver.h"
#include "detailedWeather.h"

using namespace std;

class FileWeatherObserver : public WeatherObserver {
private:
    std::string fileName;
public:
    explicit FileWeatherObserver(const std::string& fileName);
    void onWeatherUpdate(const std::string& cityName, const DetailedWeather& weather) override;
};

#endif 
