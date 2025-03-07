#ifndef WEATHER_EXCEPTION_H
#define WEATHER_EXCEPTION_H

#pragma once

#include <stdexcept>
#include <string>

using namespace std;

class WeatherException : public runtime_error {
public:
    explicit WeatherException(const string& message)
        : runtime_error(message) {}
};

#endif