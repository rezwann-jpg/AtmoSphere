#include "App.h"
#include "IconManager.h"
#include "TimeDateWidget.h"
#include "SearchBar.h"
#include "cityWeather.h"
#include "Button.h"

App::App(const std::string &title, int width, int height)
        : window(sf::VideoMode(width, height), title), service("99cf5d3f3e51411bb01ed89e384a01a4"), dashboard(sf::Vector2f(40, 90), cityManager, window) 
{
    if (!TheIconManager::getInstance().load()) {
        std::cerr << "Failed to load icons" << std::endl;
    }

    elements.push_back(new TimeDateWidget(sf::Vector2f(30, 20), sf::Vector2f(200, 50)));
    elements.push_back(new SearchBar(sf::Vector2f(300, 20), sf::Vector2f(300, 40), [this](const std::string& city){
        std::cout << "Searching for " << city << std::endl;
        auto cityW = std::make_unique<CityWeather>();
        *cityW = service.getWeatherForCity(city);
        std::cout << cityW->getWeather().getWeatherMain() << "\n";
        cityW->addObserver(fileObserver);
        cityManager.addCity(std::move(cityW));
    }));
    elements.push_back(new Button(sf::Vector2f(650, 20), sf::Vector2f(150, 40), "Refresh", [this](){
        dashboard.updateWeather();
        std::cout << "Refreshed all data\n";
    }));

    setDataFileName();
    loadSavedWeatherData();
}

App::~App() {
    for (int i = 0; i < elements.size(); i++) {
        delete elements[i];
    }

    TheIconManager::getInstance().cleanUp();
}

bool App::Running() {
    return window.isOpen();
}

void App::HandleEvents() {
    sf::Event event;
    while(window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            window.close();
        }
        else if(event.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0, 0, 
                static_cast<float>(event.size.width), 
                static_cast<float>(event.size.height));
            window.setView(sf::View(visibleArea));
            dashboard.handleResize();
        }

        dashboard.handleEvents(event);
        for (int i = 0; i < elements.size(); i++) {
            elements[i]->HandleEvent(event);
        }
    }
}

void App::Update() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    dashboard.Update(mousePosF);
    for (int i = 0; i < elements.size(); i++) {
        elements[i]->Update(mousePosF);
    }
}

void App::Draw() {
    window.clear(sf::Color(224, 244, 255));
    dashboard.drawAll();
    
    for (int i = 0; i < elements.size(); i++) {
        elements[i]->Draw(window);
    }

    window.display();
}

void App::setDataFileName() {
    fileObserver = std::make_shared<FileWeatherObserver>(dataFileName);
}

void App::loadSavedWeatherData() {
    if (!fileObserver) {
        fileObserver = std::make_unique<FileWeatherObserver>(dataFileName);
    }
    
    auto loadedData = fileObserver->loadWeatherData();
    
    cityManager.loadCities(loadedData);
}