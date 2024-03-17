#include <iostream>
#include <sstream>
#include <memory>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Constants
const std::string API_URL = "https://api.openweathermap.org/data/2.5/weather?q=Lisboa,pt&appid=01bfc1473b89420ac08c560a25c1b535";


size_t writeCallback(char *ptr, size_t size, size_t nmemb, std::string *userdata)
{
    size_t realsize = size * nmemb;
    userdata->append(ptr, realsize);
    return realsize;
}

// Perform HTTP GET request and retrieve data
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

// Extract weather information from JSON
void extractWeatherInfo(const json& weatherData) {
    try {
        double temperature = weatherData["main"]["temp"].get<double>() - 273.15;
        double humidity = weatherData["main"]["humidity"];
        double pressure = weatherData["main"]["pressure"];
        double windSpeed = weatherData["wind"]["speed"];
        std::string weatherDescription = weatherData["weather"][0]["description"];
        std::string stationName = weatherData["name"];

        // Print weather information
        std::ostringstream oss;
        oss << "---------- Current weather conditions ----------" << std::endl;
        oss << "Temperature: " << temperature << " Celsius" << std::endl;
        oss << "Humidity: " << humidity << "%" << std::endl;
        oss << "Atmospheric pressure: " << pressure << " hPa" << std::endl;
        oss << "Weather description: " << weatherDescription << std::endl;
        oss << "Wind speed: " << windSpeed << " m/s" << std::endl;
        oss << "Research station: " << stationName << std::endl;
        std::cout << oss.str();
    } catch (const json::exception& e) {
        throw std::runtime_error("Error extracting weather information: " + std::string(e.what()));
    }
}

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
