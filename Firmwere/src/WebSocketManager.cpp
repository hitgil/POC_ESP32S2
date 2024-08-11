#include "../inc/WebSocketManager.h"

WebSocketManager::WebSocketManager(const char *host, uint16_t port) : host(host), port(port)
{
}

void WebSocketManager::connect()
{
    Serial.println("Connecting to WebSocket server.");
    websocketClient.connect(host, port, "/");
    if (websocketClient.connected())
    {
        Serial.println("WebSocket Connected!");
    }
    else
    {
        Serial.println("WebSocket Connection Failed!");
    }
}

void WebSocketManager::poll()
{
    websocketClient.poll();
}

void WebSocketManager::sendBinary(const char *data, size_t length)
{
    websocketClient.sendBinary(data, length);
}

bool WebSocketManager::isConnected()
{
    return websocketClient.connected();
}
