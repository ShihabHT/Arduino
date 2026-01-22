#ifndef POST_REQUEST_H
#define POST_REQUEST_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

// Pass the API ID and the data you want to send as arguments
void sendPostRequest(String apiId, String workerId, String sheet, String status) {
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClientSecure client;
        client.setInsecure();
        HTTPClient http;

        String url = "https://script.google.com/macros/s/" + apiId + "/exec";

        http.begin(client, url.c_str());
        http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
        http.addHeader("Content-Type", "application/json");

        // Constructing JSON string using the function arguments
        String json = "{\"workerId\":\"" + workerId + "\","
                    "\"sheetName\":\"" + sheet + "\","
                    "\"entranceOrExit\":\"" + status + "\"}";

        Serial.print("Sending: ");
        Serial.println(json);

        int httpResponseCode = http.POST(json);

        if (httpResponseCode > 0) {
            String payload = http.getString();
            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);
            Serial.println("Response: " + payload);
        } else {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }

        http.end();
    } else {
        Serial.println("No wifi");
    }
}

#endif