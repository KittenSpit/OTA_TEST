#include <Arduino.h>

#include <WiFi.h>
#include <ArduinoOTA.h>

// Replace with your WiFi credentials
const char* ssid = "PHD1 2.4";
const char* password = "Andrew1Laura2";

const unsigned long delay_interval = 10000; // Blink interval in milliseconds 10000 ms = 10 seconds 
// LED pin (built-in LED is usually GPIO 2 on ESP32)
const int ledPin = 25;
bool ledState = false;

void config_OTA(){
  ArduinoOTA.setHostname("ESP32-Blink");
  ArduinoOTA.setPassword("HellCat1");
  ArduinoOTA
    .onStart([]() {
      Serial.println("Start updating...");
    })
    .onEnd([]() {
      Serial.println("\nUpdate complete!");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
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
