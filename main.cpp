#include <iostream>
#include <ctime>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

size_t writeCallback(char *ptr, int size, int nmemb, void *userdata)
{
    std::string *stream = (std::string *)userdata;
    int realsize = size * nmemb;
    stream->append(ptr, realsize);
    return realsize;
}

int main()
{
    CURL *curl;
    CURLcode res;
    std::string stream;

    time_t hh_mm;
    struct tm *data;
    char conditions[80];
    time(&hh_mm);
    data = localtime(&hh_mm);

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openweathermap.org/data/2.5/weather?q=Lisboa,pt&appid=01bfc1473b89420ac08c560a25c1b535");
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &stream);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            std::cout << "CURL error: " << curl_easy_strerror(res) << std::endl;
        }
        else
        {
            json weatherData;
            try
            {
                weatherData = json::parse(stream);
            }
            catch (json::parse_error &e)
            {
                std::cout << "Error parsing JSON: " << e.what() << std::endl;
                return 1;
            }

            try
            {

                double temperature = weatherData["main"]["temp"].get<double>() - 273.15;
                double humidity = weatherData["main"]["humidity"];
                double pressure = weatherData["main"]["pressure"];
                double windSpeed = weatherData["wind"]["speed"];
                std::string weatherDescription = weatherData["weather"][0]["description"];
                std::string stationName = weatherData["name"];

                std::cout << "---------- Current weather conditions ----------" << std::endl;
                strftime(conditions, 80, "As of: %H:%M", data);
                std::cout << conditions;

                std::cout << "\nTemperatura: " << temperature << " in Celsius" << std::endl;
                std::cout << "Humidity: " << humidity << "%" << std::endl;
                std::cout << "Atmospheric pressure: " << pressure << "hPa" << std::endl;
                std::cout << "Weather description: " << weatherDescription << std::endl;
                std::cout << "Wind speed: " << windSpeed << " m/s" << std::endl;
                std::cout << "Research station: " << stationName << std::endl;
            }
            catch (json::exception &e)
            {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
        curl_easy_cleanup(curl);
    }
    return 0;
}