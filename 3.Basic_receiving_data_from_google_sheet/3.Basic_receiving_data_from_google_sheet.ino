#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

const char* ssid = "Guest WiFi";
const char* password = "12345678";
// Google Apps Script Web App URL
String GOOGLE_WEB_API = "xxx";
String breakfast, lunch, dinner;

WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println("...");
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    HTTPClient https;
    String url="https://script.google.com/macros/s/"+GOOGLE_WEB_API+"/exec?read";
    
    //https.begin(url.c_str()); //Specify the URL and certificate
    https.begin(*client, url.c_str());
    https.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode = https.GET();

    if (httpCode > 0) {
      String payload = https.getString();
      Serial.print("HttpCode: ");
      Serial.println(httpCode);
      Serial.println("Sheet value: " + payload);

      breakfast = payload.substring(0, payload.indexOf(' '));
      String remaining = payload.substring(payload.indexOf(' ') + 1);
      lunch = remaining.substring(0, remaining.indexOf(' '));
      dinner = remaining.substring(remaining.indexOf(' ') + 1);
      
      Serial.print("breakfast: ");
      Serial.print(breakfast);
      Serial.print(" ,  lunch: ");
      Serial.print(lunch);
      Serial.print(" ,  dinner: ");
      Serial.println(dinner);
    } else {
      Serial.print("HTTP request failed, error code: " + httpCode);
    }

    https.end();  // Close connection
  } else {
    Serial.println("WiFi not connected!");
  }

  delay(5000);
}


