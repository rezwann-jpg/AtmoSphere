#ifndef DETAILED_WEATHER_HPP
#define DETAILED_WEATHER_HPP

#include "baseWeather.h"
#include "weatherException.h"
#include <ctime>

using namespace std;

class DetailedWeather : public BaseWeather {
private:
    double windSpeed;
    int windDegree;
    int visibility;
    int cloudiness;
    time_t sunrise;
    time_t sunset;
    
public:
    DetailedWeather();
    
  
    double getWindSpeed() const;
    int getWindDegree() const;
    int getVisibility() const;
    int getCloudiness() const;
    time_t getSunrise() const;
    time_t getSunset() const;
    
   
    void setWindSpeed(double speed);
    void setWindDegree(int degree);
    void setVisibility(int vis);
    void setCloudiness(int clouds);
    void setSunrise(time_t time);
    void setSunset(time_t time);
};

#endif
