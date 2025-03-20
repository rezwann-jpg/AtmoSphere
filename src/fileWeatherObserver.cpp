#include "fileWeatherObserver.h"
#include <iostream>
#include <fstream>

FileWeatherObserver::FileWeatherObserver(const string& fileName)
    : fileName(fileName) {}

void FileWeatherObserver::onWeatherUpdate(const string& cityName, const DetailedWeather& weather) {
    ofstream file(fileName, ios::out | ios::app);
    if(file.is_open()){
        file << "City: " << cityName << "\n"
             << "Temperature: " << weather.getTemperature() + 273.15 << "°C\n"
             << "Feels Like: " << weather.getFeelsLike() + 273.15 << "°C\n"
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

vector<pair<string, DetailedWeather>> FileWeatherObserver::loadWeatherData() {
    vector<std::pair<std::string, DetailedWeather>> result;
    ifstream file(fileName);
    
    if (!file.is_open()) {
        std::cout << "Could not open file: " << fileName << " for reading\n";
        return result;
    }
    
    string line;
    string currentCity;
    DetailedWeather currentWeather;
    bool inRecord = false;
    
    while (std::getline(file, line)) {
        if (line.find("City: ") == 0) {
            if (inRecord && !currentCity.empty()) {
                result.push_back({currentCity, currentWeather});
                currentWeather = DetailedWeather();
            }
            currentCity = line.substr(6);
            inRecord = true;
        }
        else if (line.find("Temperature: ") == 0) {
            std::string temp = line.substr(13);
            temp = temp.substr(0, temp.length() - 3);
            currentWeather.setTemperature(std::stof(temp));
        }
        else if (line.find("Feels Like: ") == 0) {
            std::string feels = line.substr(12);
            feels = feels.substr(0, feels.length() - 3);
            currentWeather.setFeelsLike(std::stof(feels));
        }
        else if (line.find("Humidity: ") == 0) {
            std::string humidity = line.substr(10);
            humidity = humidity.substr(0, humidity.length() - 1);
            currentWeather.setHumidity(std::stoi(humidity));
        }
        else if (line.find("Pressure: ") == 0) {
            std::string pressure = line.substr(10);
            pressure = pressure.substr(0, pressure.length() - 4);
            currentWeather.setPressure(std::stoi(pressure));
        }
        else if (line.find("Weather: ") == 0) {
            std::string weather = line.substr(9);
            size_t dashPos = weather.find(" - ");
            if (dashPos != std::string::npos) {
                std::string main = weather.substr(0, dashPos);
                std::string desc = weather.substr(dashPos + 3);
                currentWeather.setWeatherMain(main);
                currentWeather.setWeatherDescription(desc);
            }
        }
        else if (line.find("Wind Speed: ") == 0) {
            std::string speed = line.substr(12);
            speed = speed.substr(0, speed.length() - 4);
            currentWeather.setWindSpeed(std::stof(speed));
        }
        else if (line.find("Wind Degree: ") == 0) {
            std::string degree = line.substr(13);
            currentWeather.setWindDegree(std::stoi(degree));
        }
        else if (line.find("Visibility: ") == 0) {
            std::string visibility = line.substr(12);
            visibility = visibility.substr(0, visibility.length() - 2);
            currentWeather.setVisibility(std::stoi(visibility));
        }
        else if (line.find("Cloudiness: ") == 0) {
            std::string cloudiness = line.substr(12);
            cloudiness = cloudiness.substr(0, cloudiness.length() - 1);
            currentWeather.setCloudiness(std::stoi(cloudiness));
        }
        else if (line == "--------------------------") {
            if (!currentCity.empty()) {
                result.push_back({currentCity, currentWeather});
                currentCity = "";
                currentWeather = DetailedWeather();
            }
        }
    }
    
    if (inRecord && !currentCity.empty()) {
        result.push_back({currentCity, currentWeather});
    }
    
    file.close();
    std::cout << "Loaded weather data for " << result.size() << " cities from " << fileName << "\n";
    
    return result;
}
