#include "detailedWeather.h"
using namespace std;

DetailedWeather::DetailedWeather() : windSpeed(0), windDegree(0), visibility(0), cloudiness(0), sunrise(0), sunset(0) {}

double DetailedWeather::getWindSpeed() const { return windSpeed; }
int DetailedWeather::getWindDegree() const { return windDegree; }
int DetailedWeather::getVisibility() const { return visibility; }
int DetailedWeather::getCloudiness() const { return cloudiness; }
time_t DetailedWeather::getSunrise() const { return sunrise; }
time_t DetailedWeather::getSunset() const { return sunset; }

void DetailedWeather::setWindSpeed(double speed) {
    if (speed < 0 || speed > 200) {
        throw WeatherException("Wind speed out of realistic range");
    }
    windSpeed = speed;
}

void DetailedWeather::setWindDegree(int degree) {
    if (degree < 0 || degree >= 360) {
        throw WeatherException("Wind degree must be between 0 and 359");
    }
    windDegree = degree;
}

void DetailedWeather::setVisibility(int vis) {
    if (vis < 0 || vis > 100000) {
        throw WeatherException("Visibility out of realistic range");
    }
    visibility = vis;
}

void DetailedWeather::setCloudiness(int clouds) {
    if (clouds < 0 || clouds > 100) {
        throw WeatherException("Cloudiness must be between 0 and 100");
    }
    cloudiness = clouds;
}

void DetailedWeather::setSunrise(time_t time) { sunrise = time; }
void DetailedWeather::setSunset(time_t time) { sunset = time; }
