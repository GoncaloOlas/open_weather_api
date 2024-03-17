#ifndef WEATHER_API_HPP
#define WEATHER_API_HPP

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string fetchData(const std::string& url);
json parseJson(const std::string& jsonData);
void extractWeatherInfo(const json& weatherData);

#endif // WEATHER_API_HPP
