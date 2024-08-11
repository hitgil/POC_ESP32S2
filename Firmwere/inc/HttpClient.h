#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <WiFi.h>
#include "esp_camera.h"

class HttpClient
{
public:
    HttpClient(const String &serverName, int serverPort);
    bool sendImage(const String &path, const String &fileName, camera_fb_t *fb);

private:
    WiFiClient client;
    String serverName;
    int serverPort;
};

#endif
