#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <WiFi.h>

class WiFiManager
{
public:
    WiFiManager(const char *ssid, const char *password);
    void connect();
    bool isConnected();
    IPAddress getLocalIP();

private:
    const char *ssid;
    const char *password;
};

#endif
