# Weather API Client

This is a simple client application for retrieving and displaying weather information using the openweather API.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Dependencies](#dependencies)
- [Contributing](#contributing)
- [License](#license)

## Features

- Fetches weather data from the openweather API.
- Displays current weather conditions including temperature, humidity, pressure, wind speed, weather description, and location.
- Provides error handling for network requests and JSON parsing.
- Easy-to-use interface for integrating weather data into your application. (soon)

## Installation

1. Clone this repository to your local machine:

    ```bash
    git clone https://github.com/GoncaloOlas/open_weather_api.git
    ```

2. Navigate to the project directory:

    ```bash
    cd open-weather-api
    ```

3. Compile the source code:

    ```bash
    cmake .
    make
    ```

4. Run tests: (optional)

    ```bash
    ctest
    ```

## Usage

1. Run the executable:

    ```bash
    ./OpenWeatherApp
    ```

2. Follow the instructions to enter the location for which you want to retrieve weather information.(soon)

3. View the current weather conditions displayed in the console.

## Dependencies

- [CURL](https://curl.se/)
- [nlohmann/json](https://github.com/nlohmann/json) (JSON library)

Make sure to have these dependencies installed on your system before compiling the application.

## Contributing

Contributions are welcome! If you have any suggestions, improvements, or feature requests, feel free to open an issue or create a pull request.

## License

This project is licensed under the MIT license.
