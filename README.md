# FireStore_Esp8266-Esp32_ReadData_AND_ControlLED

This is a project that allows you to control LEDs connected to an ESP32 or ESP8266 using Google Firebase Firestore. You can use this project to remotely control the state of LEDs via the Firebase Firestore database.

## Getting Started

### Prerequisites

Before you get started with this project, make sure you have the following:

- An ESP32 or ESP8266 board.
- A Wi-Fi network with SSID and password.
- A Firebase project with an API key and a Firestore database.
- Arduino IDE with the necessary libraries installed.

### Installation

1. Clone this repository or download the source code.
2. Open the Arduino IDE and install the required libraries:
   - `WiFi.h` for ESP32 or `ESP8266WiFi.h` for ESP8266.
   - `Firebase_ESP_Client.h`
   - `TokenHelper.h` (provided in the `addons` folder).
   - `ArduinoJson.h`
3. Open the project in the Arduino IDE.

### Configuration

In the code, you need to set up some configuration parameters:

- Wi-Fi credentials:
  - `WIFI_SSID` and `WIFI_PASSWORD`.
- Firebase API key:
  - `API_KEY`.
- Firebase project ID:
  - `FIREBASE_PROJECT_ID`.
- Firebase user email and password:
  - `USER_EMAIL` and `USER_PASSWORD`.

### Hardware Setup

Connect your LEDs to the following pins on your ESP board:

- LED 1: D0 (or any other GPIO pin)
- LED 2: D4 (or any other GPIO pin)
- LED 3: D7 (or any other GPIO pin)

### Usage

1. Upload the code to your ESP32 or ESP8266 board.
2. Open the Serial Monitor in the Arduino IDE to monitor the device's connection to Wi-Fi and Firebase.
3. The code will periodically check the Firebase Firestore for changes in the "esp" collection and control the LEDs accordingly.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Thanks to mobizt for providing the "Firebase-ESP-Client" library for Arduino.
- Special thanks to contributors and the open-source community.

Happy tinkering!

