#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#include <Fonts/FreeSerif9pt7b.h>        // custom font to fix pixelation FreeSerif9pt7b.h- smaller
#include <Fonts/FreeSans7pt7b.h>

// Define the OLED display width and height
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_RESET -1 
#define SCREEN_ADDRESS 0x3C

String line1 = "|___Entrnace___|";
String line2 = "|_____Exit ____|";
String line3 = "______________";
String line4 = "|__Setup Wifi__|";

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
    // coordinate for 3 line text in y-axis (13, 36, 59) for FreeSerif9pt7b
    display.setFont(&FreeSerif9pt7b);        // custom font to fix pixelation
    display.setTextColor(SSD1306_WHITE);    // Draw white text
    display.setTextSize(1);    
    display.setCursor(0, 13);              // Start at top-left corner (x, y)
    display.print("Unknown location");

    display.setFont(&FreeSans7pt7b); 
    display.setCursor(0, 36);              // Start at top-left corner (x, y)
    display.print("Unknown location");

    display.setFont(NULL); 
    display.setCursor(0, 59);              // Start at top-left corner (x, y)
    display.print("Unknown location");
    
    // display.setCursor(0, 50);
    // display.setFont(NULL);                 // Sets default font
    // display.println("Unknown location!");
   
    display.display();
    delay(1000);
}

void loop() {
    showText();
}

void showText(){
    display.clearDisplay();
    
    display.setFont(&FreeSerif9pt7b);
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);    

    display.setCursor(0, 13);              // Start at top-left corner (x, y)
    display.print(line4);

    display.setCursor(0, 36);              // Start at top-left corner (x, y)
    display.print(line2);

    display.setCursor(0, 59);              // Start at top-left corner (x, y)
    display.print(line3);
   
    display.display();
}
