#include <iostream>
#include <sstream>
#include "weather_api.hpp"

const std::string API_URL = "https://api.openweathermap.org/data/2.5/weather?q=Lisboa,pt&appid=01bfc1473b89420ac08c560a25c1b535";

int main() {
    try {
        std::string jsonData = fetchData(API_URL);
        json weatherData = parseJson(jsonData);
        extractWeatherInfo(weatherData);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
