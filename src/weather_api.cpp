#include "weather_api.hpp"
#include <iostream>
#include <curl/curl.h>

size_t writeCallback(char *ptr, size_t size, size_t nmemb, std::string *userdata) {
    size_t realsize = size * nmemb;
    userdata->append(ptr, realsize);
    return realsize;
}

std::string fetchData(const std::string& url) {
    std::string data;
    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            throw std::runtime_error("Failed to fetch data");
        }

        // Print fetched data for debugging
        std::cout << "Fetched data: " << data << std::endl;

        curl_easy_cleanup(curl);
    } else {
        throw std::runtime_error("Failed to initialize curl");
    }
    return data;
}

json parseJson(const std::string& jsonData) {
    try {
        return json::parse(jsonData);
    } catch (const json::parse_error& e) {
        throw std::runtime_error("Error parsing JSON: " + std::string(e.what()));
    }
}

bool hasRequiredFields(const json& weatherData) {
    return (weatherData.contains("main") && !weatherData["main"].is_null() &&
            weatherData["main"].contains("temp") &&
            weatherData["main"].contains("humidity") && weatherData["main"].contains("pressure") &&
            weatherData.contains("wind") && weatherData["wind"].contains("speed") &&
            weatherData.contains("weather") && !weatherData["weather"].empty() &&
            weatherData["weather"][0].contains("description") && weatherData.contains("name"));
}

void printWeatherInfo(double temperature, double humidity, double pressure, double windSpeed, const std::string& weatherDescription, const std::string& stationName) {
    // Print weather information
    std::ostringstream oss;
    oss << "---------- Current weather conditions ----------" << std::endl;
    oss << "Temperature: " << std::fixed << std::setprecision(2) << temperature << " Celsius" << std::endl;
    oss << "Humidity: " << humidity << "%" << std::endl;
    oss << "Atmospheric pressure: " << pressure << " hPa" << std::endl;
    oss << "Weather description: " << weatherDescription << std::endl;
    oss << "Wind speed: " << windSpeed << " m/s" << std::endl;
    oss << "Research station: " << stationName << std::endl;
    std::cout << oss.str();
}

void extractWeatherInfo(const json& weatherData) {
    try {
        if (!hasRequiredFields(weatherData)) {
            throw std::runtime_error("Error extracting weather information: Missing or invalid fields");
        }

        double temperature = weatherData["main"]["temp"];
        double humidity = weatherData["main"]["humidity"];
        double pressure = weatherData["main"]["pressure"];
        double windSpeed = weatherData["wind"]["speed"];
        std::string weatherDescription = weatherData["weather"][0]["description"];
        std::string stationName = weatherData["name"];

        // Convert temperature to Celsius
        temperature -= 273.15;

        // Call the print function
        printWeatherInfo(temperature, humidity, pressure, windSpeed, weatherDescription, stationName);
    } catch (const std::exception& e) {
        throw std::runtime_error("Error extracting weather information: " + std::string(e.what()));
    }
}
