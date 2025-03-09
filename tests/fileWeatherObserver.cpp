#include "fileWeatherObserver.h"
#include <iostream>
#include <fstream>

FileWeatherObserver::FileWeatherObserver(const string& fileName)
    : fileName(fileName) {}

void FileWeatherObserver::onWeatherUpdate(const string& cityName, const DetailedWeather& weather) {
    ofstream file(fileName, ios::out | ios::app);
    if(file.is_open()){
        file << "City: " << cityName << "\n"
             << "Temperature: " << weather.getTemperature() << "°C\n"
             << "Feels Like: " << weather.getFeelsLike() << "°C\n"
             << "Humidity: " << weather.getHumidity() << "%\n"
             << "Pressure: " << weather.getPressure() << " hPa\n"
             << "Weather: " << weather.getWeatherMain() << " - " << weather.getWeatherDescription() << "\n"
             << "Wind Speed: " << weather.getWindSpeed() << " m/s\n"
             << "Wind Degree: " << weather.getWindDegree() << "\n"
             << "Visibility: " << weather.getVisibility() << " m\n"
             << "Cloudiness: " << weather.getCloudiness() << "%\n"
             << "--------------------------\n";
        file.close();
        cout << "Weather data saved for " << cityName << " to " << fileName << "\n";
    } else {
        cout << "Failed to open file: " << fileName << "\n";
    }
}
