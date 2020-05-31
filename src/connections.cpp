#include <connections.h>

WiFiClient wclient;
PubSubClient MQTTclient(wclient);

char MQTT_HSV[64];
char MQTT_HSV_SET[64];
char MQTT_STATE[64];

void setupWiFi(config cfg){
    Serial.println("WiFi setup");
    WiFi.hostname(cfg.device_id);
    WiFi.begin(cfg.wifi.ssid, cfg.wifi.password);
    Serial.println();

    byte connCount = 0;
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        connCount++;
        Serial.print("Connetion attempts ");
        Serial.println(connCount);
        if (connCount >= 30) {
            Serial.println("Restart and try again");
            ESP.restart();
        }
    }

    Serial.println("WiFi ready!");
    Serial.print("Connected to ");
    Serial.println(cfg.wifi.ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void publishHSV(){
    char c[12];
    sprintf(c, "%d,%d,%d", iHSV[0], iHSV[1], iHSV[2]);
    MQTTclient.publish(MQTT_HSV, c, true);
    if((int)iHSV[2] > 0){
        MQTTclient.publish(MQTT_STATE, "true", true);
    }else{
        MQTTclient.publish(MQTT_STATE, "false", true);
    }
}

void callbackMQTT(char* p_topic, byte* p_payload, unsigned int p_length) {
    // concat the payload into a string
    String payload;
    for (uint8_t i = 0; i < p_length; i++) {
    payload.concat((char)p_payload[i]);
    }
    //Debug payload data to serial console
    Serial.println(p_topic);
    Serial.println(payload);

    if (strcmp(MQTT_HSV_SET,p_topic) == 0) {
        hsv HSV = MQTTThingHSVScale(payload);
        rgb RGB = hsv2rgb(HSV);
        analogWrite(redPin, RGB.r * 255);
        analogWrite(greenPin, RGB.g * 255);
        analogWrite(bluePin, RGB.b * 255);
        publishHSV();
    }
}

void setupMQTT(config cfg){
    MQTTclient.setServer(cfg.mqtt.host, cfg.mqtt.port);
    MQTTclient.setCallback(callbackMQTT);
}

void connectMQTT(config cfg) {
    strcpy(MQTT_HSV_SET, cfg.mqtt.base_topic);
    strcat(MQTT_HSV_SET, cfg.device_id);
    strcat(MQTT_HSV_SET, "/hsv/set");
    strcpy(MQTT_HSV, cfg.mqtt.base_topic);
    strcat(MQTT_HSV, cfg.device_id);
    strcat(MQTT_HSV, "/hsv");
    strcpy(MQTT_STATE, cfg.mqtt.base_topic);
    strcat(MQTT_STATE, cfg.device_id);
    strcat(MQTT_STATE, "/state");  
    
    // Loop until we're reconnected
    while (!MQTTclient.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (MQTTclient.connect(cfg.device_id, cfg.mqtt.username, cfg.mqtt.password)) {
            char topic[64];
            strcpy(topic, cfg.mqtt.base_topic);
            strcat(topic, cfg.device_id);
            strcat(topic, "/#");
            MQTTclient.subscribe(topic);
            Serial.println("connected");
            // Once connected, return
        } else {
            Serial.print("failed, rc=");
            Serial.print(MQTTclient.state());
            Serial.println(" try again in 5 seconds");
            delay(5e3);
        }
    }
}


