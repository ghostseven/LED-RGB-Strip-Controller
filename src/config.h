#ifndef CONFIG_H
#define CONFIG_H

#include <ArduinoJson.h>
#include <FS.h>

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */

class config_wifi
{
    public:
        char ssid[64];
        char password[64];
};
class config_mqtt
{
    public:
        char host[64];
        int port;
        char base_topic[26];
        char username[64];
        char password[64];
};
class config
{
    public:
        char name[26];
        char device_id[26];
        int deep_sleep_interval;
        config_wifi wifi;
        config_mqtt mqtt;
        bool load();
    private:
        bool loadConfig();
};
#endif