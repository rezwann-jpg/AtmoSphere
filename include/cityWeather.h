#ifndef CITY_WEATHER_HPP
#define CITY_WEATHER_HPP

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "detailedWeather.h"
#include "weatherObserver.h"
#include "weatherException.h"


class CityWeather {
private:
    string cityName;
    string countryCode;
    double latitude;
    double longitude;
    int timezone;
    DetailedWeather weather;
    vector<weak_ptr<WeatherObserver>> observers;
    
public:
    CityWeather();
    
   
    void addObserver(const shared_ptr<WeatherObserver>& observer);
    void notifyObservers();
    
    string getCityName() const;
    string getCountryCode() const;
    double getLatitude() const;
    double getLongitude() const;
    int getTimezone() const;
    const DetailedWeather& getWeather() const;
    DetailedWeather& getWeatherRef();
    
    void setCityName(const string& name);
    void setCountryCode(const string& code);
    void setLatitude(double lat);
    void setLongitude(double lon);
    void setTimezone(int tz);
    
    void updateWeather(const DetailedWeather& newWeather);
    
    void display() const;
};

#endif 
