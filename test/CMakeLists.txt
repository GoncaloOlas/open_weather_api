# Locate Catch2 package
find_package(Boost REQUIRED COMPONENTS system)
find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(CURL REQUIRED)
find_package(Catch2 REQUIRED)

# Add executable for your test program
add_executable(test_weather_api 
    test_weather_api.cpp
    ../src/weather_api.cpp
)

# Link the Catch2 library to the test executable
# target_link_libraries(test_weather_api Catch2::Catch2)
target_link_libraries(test_weather_api Catch2::Catch2 Boost::system nlohmann_json::nlohmann_json CURL::libcurl)

# Set the include directories
include_directories(${CATCH2_INCLUDE_DIRS})

# Add tests
include(CTest)
include(Catch)
catch_discover_tests(test_weather_api)
