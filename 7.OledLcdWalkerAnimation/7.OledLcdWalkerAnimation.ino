#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "walker_animation.h" // Include the other file

// Define the OLED display width and height
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_RESET -1 
#define SCREEN_ADDRESS 0x3C

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The ESP32 default I2C pins are 21 (SDA) and 22 (SCL)
// The ESP8266 default I2C pins are D2 (SDA) and D1 (SCL)
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);

void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever if display fails
  }

  // Trigger the animation once during setup for 2 seconds (2000ms)
  playWalkingAnimation(display, -1);
}

void loop() {
  // Example: Play animation again every time something happens
  // playWalkingAnimation(display, 2000);
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Animation Finished!");
  display.display();
  delay(2000);
}