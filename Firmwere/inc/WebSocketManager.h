#ifndef WEBSOCKETMANAGER_H
#define WEBSOCKETMANAGER_H

#include <ArduinoWebsockets.h>

class WebSocketManager
{
public:
    WebSocketManager(const char *host, uint16_t port);
    void connect();
    void poll();
    void sendBinary(const char *data, size_t length);
    bool isConnected();

private:
    WebsocketsClient websocketClient;
    const char *host;
    uint16_t port;
};

#endif
