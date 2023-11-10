//For Both Esp32 and Esp8266
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <ArduinoJson.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "AR~Yan"
#define WIFI_PASSWORD "00000000"

/* 2. Define the API Key */
#define API_KEY "AIzaSyBI8gDd6XTD2r6D_RuzoFwaY8RmPrgUMBA"

/* 3. Define the project ID */
#define FIREBASE_PROJECT_ID "espfirestore-7b1b9"

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "aryantfk5@gmail.com"
#define USER_PASSWORD "zxcvbnm123"

/* Define the pins for the LEDs */
#define LED_PIN_CONTROL1 D0
#define LED_PIN_CONTROL2 D4
#define LED_PIN_CONTROL3 D7
//#define LED_PIN_CONTROL4 D8  //define Pin For 4th LED

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

String path;

void setup() {

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback;  //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);

  Firebase.reconnectWiFi(true);

   /* Set LED pins as OUTPUT */
    pinMode(LED_PIN_CONTROL1, OUTPUT);
    pinMode(LED_PIN_CONTROL2, OUTPUT);
    pinMode(LED_PIN_CONTROL3, OUTPUT);
 // pinMode(LED_PIN_CONTROL4, OUTPUT);  //pinMode For 4th LED
}

void loop() {           

  String path = "esp";

    Serial.print("Get entire collection... ");
    if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", path.c_str(), ""))
    {
        Serial.println("ok");

        StaticJsonDocument<1024> doc;
        DeserializationError error = deserializeJson(doc, fbdo.payload().c_str());

        if (!error)
        {
            for (JsonObject document : doc["documents"].as<JsonArray>())
            {
                const char *document_name = document["name"];
                Serial.print(document_name);

                const char *document_fields_state_stringValue = document["fields"]["state"]["stringValue"];
                Serial.print(" : ");
                Serial.println(document_fields_state_stringValue);

                int stateValue = atoi(document_fields_state_stringValue);

                if (strstr(document_name, "Control 1") != nullptr)
                {
                    digitalWrite(LED_PIN_CONTROL1, stateValue);
                    stateValue ? Serial.print("Control 1 On"): Serial.print("Control 1 OFF");
                     
                }
                else if (strstr(document_name, "Control 2") != nullptr)
                {
                    digitalWrite(LED_PIN_CONTROL2, stateValue);
                    stateValue ? Serial.print("Control 2 On"): Serial.print("Control 2 OFF");
                }
                else if (strstr(document_name, "Control 3") != nullptr)
                {
                    digitalWrite(LED_PIN_CONTROL3, stateValue);
                    stateValue ? Serial.print("Control 3 On"): Serial.print("Control 3 OFF");
                }
//add 4th Led
               // else if (strstr(document_name, "Control 4") != nullptr)
               //  {
               //      digitalWrite(LED_PIN_CONTROL4, stateValue);
               //      stateValue ? Serial.print("Control 4 On"): Serial.print("Control 4 OFF");
               //  }
              
            }
        }
    }

    delay(7000);
}
