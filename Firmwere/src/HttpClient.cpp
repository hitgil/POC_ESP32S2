#include "../inc/HttpClient.h"

HttpClient::HttpClient(const String &serverName, int serverPort)
    : serverName(serverName), serverPort(serverPort)
{
}


bool HttpClient::sendImage(const String &path, const String &fileName, camera_fb_t *fb)
{
    if (client.connect(serverName.c_str(), serverPort))
    {
        String boundary = "----Boundary";
        String head = "--" + boundary + "\r\n" +
                      "Content-Type: image/jpeg\r\n\r\n";
        String tail = "\r\n--" + boundary + "--\r\n";

        uint32_t totalLen = fb->len + head.length() + tail.length();

        client.println("POST " + path + " HTTP/1.1");
        client.println("Host: " + serverName);
        client.println("Content-Length: " + String(totalLen));
        client.println("Content-Type: multipart/form-data; boundary=" + boundary);
        client.println();
        client.print(head);

        
        size_t bufferSize = 1024;
        for (size_t n = 0; n < fb->len; n += bufferSize)
        {
            size_t chunkSize = min(bufferSize, fb->len - n);
            client.write(fb->buf + n, chunkSize);
        }

        client.print(tail);

        
        unsigned long startTime = millis();
        while (millis() - startTime < 10000)
        {
            if (client.available() > 0)
            {
                String response = client.readStringUntil('\n');
                if (response == "\r")
                {
                    break;
                }
            }
        }

        client.stop();
        return true;
    }
    else
    {
        Serial.println("HTTP Connection to " + serverName + " failed.");
        return false;
    }
}
