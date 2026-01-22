#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#include <Fonts/FreeSerif9pt7b.h>        // custom font to fix pixelation FreeSerif9pt7b.h- smaller
#include <Fonts/FreeSans9pt7b.h>         // custom font to fix pixelation FreeSans9pt7b.h
#include <Fonts/Org_01.h>
#include <Fonts/Tiny3x3a2pt7b.h>

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
    Serial.begin(115200);

    // Initialize the SSD1306 display
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {  // Address 0x3C for 128x64
        Serial.println(F("SSD1306 allocation failed"));
    for (;;);  // Don't proceed, loop forever
    }

    // Clear the display buffer
    display.clearDisplay();
    
    display.setFont(&FreeSerif9pt7b);        // custom font to fix pixelation
    display.setTextColor(SSD1306_WHITE);    // Draw white text
    display.setTextSize(1);    
    display.setCursor(0, 13);              // Start at top-left corner (x, y)
    display.println("Unknown location!");
    
    display.setCursor(0, 50);
    display.setFont(NULL);                 // Sets default font
    display.println("Unknown location!");
    // Update the screen with the buffer contents
    display.display();
}

void loop() {
    // Nothing needed in the loop for this basic example
}

// void showText()
