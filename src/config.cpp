#include <config.h>

bool config::loadConfig(){
    File configFile = SPIFFS.open("/config.json", "r");
    if(!configFile){
        Serial.println("Failed to open cionfig file");
        return false;
    }

    size_t size = configFile.size();
    if (size > 1024) {
        Serial.println("Config file size is too large");
        return false;
    }    
    // Allocate a buffer to store contents of the file.
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);

    StaticJsonDocument<500> doc;
    auto error = deserializeJson(doc, buf.get());
    if (error) {
        Serial.println("Failed to parse config file");
        return false;
    }

    strcpy(name, doc["name"]);
    strcpy(device_id, doc["device_id"]);

    deep_sleep_interval = doc["deep_sleep_interval"]; 
    strcpy(wifi.ssid, doc["wifi"]["ssid"]);
    strcpy(wifi.password, doc["wifi"]["password"]);

    strcpy(mqtt.host, doc["mqtt"]["host"]);
    mqtt.port = doc["mqtt"]["port"];
    strcpy(mqtt.base_topic, doc["mqtt"]["base_topic"]);
    strcpy(mqtt.username, doc["mqtt"]["username"]);
    strcpy(mqtt.password, doc["mqtt"]["password"]);
    return true;
}

bool config::load(){
    Serial.println("Mounting FS...");
    if (!SPIFFS.begin()) {
        Serial.println("Failed to mount file system");
        return false;
    }

    if (!loadConfig()) {
        Serial.println("Failed to load config");
        return false;
    } else {
        Serial.println("Config loaded");
        return true;
    }    
}