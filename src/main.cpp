#include <Arduino.h>
#include <ArduinoOTA.h>

#ifdef USE_8266
  #include <ESP8266WiFi.h>
#endif

#ifndef USE_8266
  #include <WiFi.h>
#endif


// Replace with your WiFi credentials
const char* ssid = "PHD1 2.4";
const char* password = "Andrew1Laura2";

const unsigned long delay_interval = 1000; // Blink interval in milliseconds 10000 ms = 10 seconds 
// LED pin (built-in LED is usually GPIO 2 on ESP32)

bool ledState = false;

#ifndef LED_PIN
#define LED_PIN 2
#endif

#ifndef DEVICE_HOSTNAME
#define DEVICE_HOSTNAME "8266-blink3"
#endif

const int ledPin = LED_PIN;

void config_OTA(){
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)



  //Serial.println(TOSTRING(DEVICE_HOSTNAME));  
ArduinoOTA.setPort(3232);
  ArduinoOTA.setHostname(TOSTRING(DEVICE_HOSTNAME));
  //ArduinoOTA.setHostname("esp32-blink2");

  ArduinoOTA.setPassword("HellCat1");
  ArduinoOTA.onStart([]() {
      Serial.println("Start updating...");
    });
    ArduinoOTA.onEnd([]() {
      Serial.println("\nUpdate complete!");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 1000)));
    }); 
    ArduinoOTA.onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();
  Serial.println("OTA Ready!");
}



void setup() {
  Serial.begin(115200);
  Serial.println("Booting...");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


//--------------------------------------------------------------------
  // Configure OTA
config_OTA();
//--------------------------------------------------------------------
  pinMode(ledPin, OUTPUT);
}

void loop() {
  ArduinoOTA.handle(); // Always process OTA requests

  // Blink LED
  static unsigned long lastToggle = 0;
  if (millis() - lastToggle > delay_interval) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    lastToggle = millis();
  }
}
