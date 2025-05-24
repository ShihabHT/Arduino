#include <ESP8266WiFi.h>

const char* ssid = "Guest WiFi";
const char* password = "123456789";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println("...");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // if (WiFi.status() == WL_CONNECTED) {
  //   Serial.println("WiFi connected...");
  // }
  // else {
  //   Serial.println("WiFi disconnected!");
  // }
  // delay(5000);
  
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j <= i; j++) {
      Serial.print("* ");
    }
    Serial.println();
    delay(1000);
  }


  for (int i = 10; i > 0; i--) {
    for (int j = 0; j < i; j++) {
      Serial.print("* ");
    }
    Serial.println();
    delay(1000);
  }
  delay(5000);
}








