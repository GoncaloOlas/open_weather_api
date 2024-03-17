cmake_minimum_required(VERSION 3.10)
project(OpenWeatherApp)

# Locate the necessary packages
find_package(Boost REQUIRED COMPONENTS system)
find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(CURL REQUIRED)
include(CTest)  # Include CTest for testing functionality

# Set the include directories
include_directories(include)

# Set the source files
set(SOURCES 
    src/main.cpp
    src/weather_api.cpp
)

# Create the executable
add_executable(OpenWeatherApp ${SOURCES})

# Link necessary libraries
target_link_libraries(OpenWeatherApp Boost::system nlohmann_json::nlohmann_json CURL::libcurl)

# If testing is enabled, include the test directory
if(BUILD_TESTING)
    add_subdirectory(test)  # Include tests
endif()
