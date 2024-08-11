#include "../inc/WiFiManager.h"


WiFiManager::WiFiManager(const char *ssid, const char *password) : ssid(ssid), password(password)
{
}

void WiFiManager::connect()
{
    WiFi.begin(ssid, password);
    WiFi.setSleep(false);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
}

bool WiFiManager::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

IPAddress WiFiManager::getLocalIP()
{
    return WiFi.localIP();
}
