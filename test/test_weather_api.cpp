#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../include/weather_api.hpp"

TEST_CASE("Test fetchData function")
{
    // This is a mock test case since fetchData depends on an external API
    // Replace with actual test cases if possible
    // REQUIRE(fetchData("https://example.com").size() > 0);
    // REQUIRE(fetchData("https://invalid-url.com") == "");
}

TEST_CASE("Test parseJson function")
{
    // Test valid JSON data
    SECTION("Valid JSON data")
    {
        std::string jsonData = "{\"key\": \"value\"}";
        REQUIRE_NOTHROW(parseJson(jsonData));
    }

    // Test invalid JSON data
    SECTION("Invalid JSON data")
    {
        std::string invalidJsonData = "{invalid_json_data}";
        REQUIRE_THROWS(parseJson(invalidJsonData));
    }
}

TEST_CASE("Test extractWeatherInfo function")
{
    // Test valid weather data
    SECTION("Valid weather data")
    {
        nlohmann::json weatherData = {
            {"base", "stations"},
            {"clouds", {{"all", 20}}},
            {"cod", 200},
            {"coord", {{"lat", 38.7167}, {"lon", -9.1333}}},
            {"dt", 1710693017},
            {"id", 2267057},
            {"main", {{"feels_like", 298.23}, {"humidity", 41}, {"pressure", 1018}, {"temp", 298.56}, {"temp_max", 298.56}, {"temp_min", 294.06}}},
            {"name", "Lisbon"},
            {"sys", {{"country", "PT"}, {"id", 6901}, {"sunrise", 1710657857}, {"sunset", 1710701120}, {"type", 1}}},
            {"timezone", 0},
            {"visibility", 10000},
            {"weather", {{{"description", "few clouds"}, {"icon", "02d"}, {"id", 801}, {"main", "Clouds"}}}},
            {"wind", {{"deg", 220}, {"speed", 3.09}}}};
        REQUIRE_NOTHROW(extractWeatherInfo(weatherData));
    }

    // Test invalid weather data
    SECTION("Invalid weather data")
    {
        // Missing required fields
        nlohmann::json invalidWeatherData = {
            {"main", {}}, // Missing required fields
            {"wind", {{"speed", 10.0}}},
            {"weather", {{"description", "Cloudy"}}},
            {"name", "City"}};
        REQUIRE_THROWS(extractWeatherInfo(invalidWeatherData));
    }
}
