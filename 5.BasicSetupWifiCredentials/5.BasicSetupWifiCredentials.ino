#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager


void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Initializing Hotspot...");
  Serial.print("Please, connect to: ");
  Serial.println(myWiFiManager->getConfigPortalSSID());
  Serial.println(WiFi.softAPIP());

}

void setup() {
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    // it is a good practice to make sure your code sets wifi mode how you want it.

    // put your setup code here, to run once:
    Serial.begin(115200);
    
    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;

    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
    // wm.resetSettings();

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result

    bool res;
    const char* HotspotName = "SetupESP";
    const char* HotspotPass = "esp12345";

    wm.setConfigPortalTimeout(180); //sets a time limit for config portal. after timeout, the autoConnect function will return, no matter the outcome
    wm.setAPCallback(configModeCallback); // setAPCallBack() is a call back function runs before entering configuration mode. should be placed before autoConnect()

    // res = wm.autoConnect(); // auto generated AP name from chipid
    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
    res = wm.autoConnect(HotspotName, HotspotPass); // password protected ap
    //wm.startConfigPortal(HotspotName, HotspotPass); //to manually start the configuration portal on demand. in this case use "WiFi.status() == WL_CONNECTED" to check status

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
    // put your main code here, to run repeatedly:  
    if (WiFi.status() == WL_CONNECTED) { //WiFiManager is a wrapper for standard WiFi libraries. Once it has configured the connection, you should use the standard WiFi.status()
        // Device is currently connected
        Serial.println("Connected");
    } else {
        Serial.println("Not connected");
    }
    
    delay(5000); 
}
