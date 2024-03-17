cmake_minimum_required(VERSION 3.10)

# Set the project name
project(OpenWeatherApp)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# subdirectories
add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(test)