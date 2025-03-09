#ifndef ICONSET_H
#define ICONSET_H

#pragma once

#include "Icon.h"
#include <unordered_map>
#include <string>

class IconSet {
public:
    IconSet();
    ~IconSet();

    bool addIcon(const std::string& weatherCondition, const std::string& filePath);
    sf::Sprite getIcon(const std::string& weatherCondition) const;
    void clear();

private:
    std::unordered_map<std::string, Icon> icons;

};

#endif