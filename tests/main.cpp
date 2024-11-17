#include <SFML/Network.hpp>
#include <iostream>
#include <string>

int main() {
    sf::Http http("http://api.openweathermap.org");

    std::string apiKey = "99cf5d3f3e51411bb01ed89e384a01a4";
    std::string city = "Dhaka";
    std::string endpoint = "/data/2.5/weather?q=" + city + "&appid=" + apiKey;

    sf::Http::Request request(endpoint, sf::Http::Request::Get);

    sf::Http::Response response = http.sendRequest(request);

    if (response.getStatus() == sf::Http::Response::Ok) {
        std::cout << "Response received successfully!" << std::endl;
        std::cout << "Data: " << response.getBody() << std::endl;
    } else {
        std::cerr << "HTTP error: " << response.getStatus() << std::endl;
    }

    return 0;
}
