/*
    Programming a button is a "rite of passage" in Arduino. 
    While it sounds simple, physical buttons have a few 
    quirks—specifically floating pins and contact bounce.

    Here is the most reliable way to set it up using the built-in 
    pull-up resistor (which saves you from having to wire up extra 
    external resistors).

    1. The Wiring
        Connect one leg of the button to Digital Pin D2 (or any GPIO) 
        and the other leg to GND.

    2. The Code (Basic)
        By using INPUT_PULLUP, the pin will stay HIGH (3.3V/5V) when 
        the button is not pressed. When you press it, the pin connects 
        to GND and becomes LOW.
*/

#define BUTTON_PIN D2 // Pin connected to the button
#define LED_PIN D4    // Built-in LED on most ESP8266/Arduinos

void setup() {
  Serial.begin(115200);
  
  // Use INPUT_PULLUP to avoid "floating" pin issues
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Read the state: LOW means pressed, HIGH means not pressed
  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW) {
    Serial.println("Button Pressed!");
    digitalWrite(LED_PIN, LOW); // Turn LED on (Active Low)
  } else {
    digitalWrite(LED_PIN, HIGH); // Turn LED off
  }
}


