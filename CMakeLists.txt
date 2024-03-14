cmake_minimum_required(VERSION 3.10)

# Set the project name
project(OpenWeatherApp)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Boost
find_package(Boost REQUIRED COMPONENTS system)
find_package(nlohmann_json 3.2.0 REQUIRED)
find_package( CURL REQUIRED )

# Add the executable
add_executable(OpenWeatherApp main.cpp)

# Link Boost to the executable
target_link_libraries(OpenWeatherApp PRIVATE Boost::system nlohmann_json::nlohmann_json CURL::libcurl)