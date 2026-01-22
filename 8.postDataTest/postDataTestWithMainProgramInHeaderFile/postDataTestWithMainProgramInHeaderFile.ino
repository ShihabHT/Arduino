#include <WiFiManager.h>
#include "postRequest.h" // Include your custom header

String GOOGLE_WEB_API = "xxx";

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Hotspot name: ");
  Serial.print(myWiFiManager->getConfigPortalSSID());
//   Serial.println(WiFi.softAPIP());
}

void setup() {
    WiFi.mode(WIFI_STA);
    Serial.begin(115200);
    WiFiManager wm;
    
    const char* HotspotName = "SetupESP";
    const char* HotspotPass = "12341234";
    wm.setConfigPortalTimeout(180);
    wm.setAPCallback(configModeCallback);

    if(!wm.autoConnect(HotspotName, HotspotPass)) { 
        Serial.println("Failed to connect...");
    } else {
        Serial.println("connected...)");
    }
}

void loop() {
    // Call the function from the header file
    // Arguments: API_ID, workerId, sheetName, entranceOrExit
    sendPostRequest(GOOGLE_WEB_API, "102", "Supervisor", "0");

    delay(10000); // 10 seconds
}