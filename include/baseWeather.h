#ifndef BASE_WEATHER_H
#define BASE_WEATHER_H

#pragma once

#include "weatherException.h"
#include <string>

using namespace std;

class BaseWeather {
protected:
    double temperature;
    double feelsLike;
    int humidity;
    int pressure;
    string weatherMain;
    string weatherDescription;
    
public:
    BaseWeather();
    virtual ~BaseWeather() = default;
    
    // Get functions
    double getTemperature() const;
    double getFeelsLike() const;
    int getHumidity() const;
    int getPressure() const;
    const string& getWeatherMain() const;
    const string& getWeatherDescription() const;
    
    //Set functions (conversion -> K to C)
    void setTemperature(double temp);
    void setFeelsLike(double feels);
    void setHumidity(int h);
    void setPressure(int p);
    void setWeatherMain(const string& main);
    void setWeatherDescription(const string& desc);
};

#endif 
