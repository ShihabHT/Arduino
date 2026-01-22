#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <WiFiManager.h>
// const char* ssid = "SHIHAB";
// const char* password = "12345678";

String GOOGLE_WEB_API = "xxx";


void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Initializing Hotspot...");
  Serial.print("Please, connect to: ");
  Serial.println(myWiFiManager->getConfigPortalSSID());
  Serial.println(WiFi.softAPIP());

}

void setup() {
    WiFi.mode(WIFI_STA);
    Serial.begin(115200);
    WiFiManager wm;
    
    bool  res;
    const char* HotspotName = "SetupESP";
    const char* HotspotPass = "esp12345";
    wm.setConfigPortalTimeout(180); //sets a time limit for config portal. after timeout, the autoConnect function will return, no matter the outcome
    wm.setAPCallback(configModeCallback); // setAPCallBack() is a call back function runs before entering configuration mode. should be placed before autoConnect()

    res = wm.autoConnect(HotspotName, HotspotPass);

    if(!res) { 
        Serial.println("Failed to connect...");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
    }
}

void loop() {
    if(WiFi.status()== WL_CONNECTED){
        WiFiClientSecure client;
        client.setInsecure();
        HTTPClient http;
        String url = "https://script.google.com/macros/s/"+GOOGLE_WEB_API+"/exec";
        
        // Your Domain name with URL path or IP address with path
        http.begin(client, url.c_str());
        http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
        // If you need an HTTP request with a content type: application/json, use the following:
        http.addHeader("Content-Type", "application/json");
        String json =
        "{\"workerId\":\"102\","
        "\"sheetName\":\"Supervisor\","
        "\"entranceOrExit\":\"0\"}";
        int httpResponseCode = http.POST(json);

    //   If you need an HTTP request with a content type: text/plain
    //   http.addHeader("Content-Type", "text/plain");
    //   int httpResponseCode = http.POST("Hello, World!");
        
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);

        if (httpResponseCode > 0) {
            String payload = http.getString();
            Serial.println("Response:");
            Serial.println(payload);
        }
        else {
            Serial.println("Error: " + httpResponseCode);
        }
        // Free resources
        http.end();
    }
    else {
        Serial.println("Connect wifi");
    }
    delay(5000);
}






