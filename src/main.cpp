#include <Arduino.h>
#include <config.h>
#include <utility.h>
#include <connections.h>
config cfg;

int redPin = D8;
int greenPin = D7;
int bluePin = D6;

void setup() {
  Serial.begin(115200);
  analogWriteRange(255);
  
  // Initialize RGB Led strip pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  cfg.load();

  setupWiFi(cfg);
  setupMQTT(cfg);
  connectMQTT(cfg);
}

void loop() {
  yield();// Stop ESP8266 from crashing, yea must yield.
  digitalWrite(LED_BUILTIN, HIGH);
  if (!MQTTclient.connected()){
      connectMQTT(cfg);
  }
  MQTTclient.loop();
}