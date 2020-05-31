#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <utility.h>
#include <config.h>

extern WiFiClient wclient;
extern PubSubClient MQTTclient;
extern int redPin;
extern int greenPin;
extern int bluePin;

void setupWiFi(config cfg);
void setupMQTT(config cfg);
void connectMQTT(config cfg);

#endif