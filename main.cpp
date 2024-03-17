#include <iostream>
#include <sstream>
#include <chrono>
#include <span>
#include <memory>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

size_t writeCallback(char *ptr, size_t size, size_t nmemb, std::string &userdata)
{
    size_t realsize = size * nmemb;
    userdata.append(ptr, realsize);
    return realsize;
}

int main()
{
    CURL *curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize curl." << std::endl;
        return 1;
    }

    std::string stream;
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.openweathermap.org/data/2.5/weather?q=Lisboa,pt&appid=01bfc1473b89420ac08c560a25c1b535");
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &stream);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
        return 1;
    }

    try {
        json weatherData = json::parse(stream);

        double temperature = weatherData["main"]["temp"].get<double>() - 273.15;
        double humidity = weatherData["main"]["humidity"];
        double pressure = weatherData["main"]["pressure"];
        double windSpeed = weatherData["wind"]["speed"];
        std::string weatherDescription = weatherData["weather"][0]["description"];
        std::string stationName = weatherData["name"];

        std::ostringstream oss;
        oss << "---------- Current weather conditions ----------" << std::endl;
        oss << "Temperature: " << temperature << " Celsius" << std::endl;
        oss << "Humidity: " << humidity << "%" << std::endl;
        oss << "Atmospheric pressure: " << pressure << " hPa" << std::endl;
        oss << "Weather description: " << weatherDescription << std::endl;
        oss << "Wind speed: " << windSpeed << " m/s" << std::endl;
        oss << "Research station: " << stationName << std::endl;

        std::cout << oss.str();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    curl_easy_cleanup(curl);
    return 0;
}
