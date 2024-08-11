#include <Arduino.h>
#include "../inc/CameraConfig.h"
#include "../inc/WiFiManager.h"
#include "../inc/WebSocketManager.h"
#include "../inc/HttpClient.h"

// Wi-Fi credentials
const char *ssid = "*******";
const char *password = "*******";

// Server details
String serverName = "192.168.157.***"; 
const int serverPort = 3000;           
String serverPath = "/images";
String fileName = "ESP32-S2";

String websockets_server_host = "192.168.157.***"; 
const uint16_t websockets_server_port = 3000;      

const int pictureInterval = 120000; 
unsigned long latestPicture = 0;

CameraConfig cameraConfig;
WiFiManager wifiManager(ssid, password);
WebSocketManager websocketManager(websockets_server_host.c_str(), websockets_server_port);
HttpClient httpClient(serverName, serverPort);

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.println();

    // Initialize camera
    if (cameraConfig.init() != ESP_OK)
    {
        Serial.println("Camera initialization failed");
        return;
    }

    // Connect to Wi-Fi
    wifiManager.connect();
    Serial.print("ESP32-CAM IP Address: ");
    Serial.println(wifiManager.getLocalIP());

    // Connect to WebSocket server
    websocketManager.connect();
}

void loop()
{
    unsigned long currentMilliseconds = millis();
    if (currentMilliseconds - latestPicture >= pictureInterval)
    {
        camera_fb_t *fb = esp_camera_fb_get();
        if (fb)
        {
            httpClient.sendImage(serverPath, fileName, fb);

            if (websocketManager.isConnected())
            {
                websocketManager.sendBinary((const char *)fb->buf, fb->len);
            }
            else
            {
                Serial.println("WebSocket Connection Lost. Reconnecting...");
                websocketManager.connect();
            }

            esp_camera_fb_return(fb);
        }
        else
        {
            Serial.println("Camera capture failed");
            delay(1000);
            ESP.restart();
        }

        latestPicture = currentMilliseconds;
    }

    // Poll WebSocket
    websocketManager.poll();
}
