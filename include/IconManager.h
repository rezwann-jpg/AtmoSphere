#ifndef ICONMANAGER_H
#define ICONMANAGER_H

#pragma once

#include "IconSet.h"

class IconManager {
public:
    ~IconManager();

    bool load();
    void cleanUp();
    sf::Sprite getIcon(const std::string& weatherCondition) const;

    static IconManager& getInstance();

    IconManager(const IconManager&) = delete;
    IconManager& operator=(const IconManager&) = delete;

private:
    IconSet iconSet;
    IconManager();

};

#endif