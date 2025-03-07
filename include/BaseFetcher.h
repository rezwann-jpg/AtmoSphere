#ifndef BASEFETCHER_H
#define BASEFETCHER_H

#pragma once

#include <string>

class BaseFetcher {
public:
    BaseFetcher(const std::string& apiKey);
    virtual ~BaseFetcher();

    virtual std::string fetchData(const std::string& city) = 0;
protected:
    std::string m_apiKey;
};

#endif