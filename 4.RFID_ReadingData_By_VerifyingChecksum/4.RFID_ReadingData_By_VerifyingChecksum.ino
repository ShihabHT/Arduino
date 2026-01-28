// #include <SoftwareSerial.h>
#include "rfid_reader.h"

// #define RFID_RX D5 
// #define RFID_TX -1    // dummy (no TX)
#define LED D4

// SoftwareSerial rfid(RFID_RX, RFID_TX);

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  rfid.begin(9600);
  Serial.println("\nESP8266 RFID Reader with Checksum Verification Ready...");
}

void loop() {
  digitalWrite(LED, HIGH);
  unsigned long  x = getRFIDTag();
  if(x == -1){
    Serial.println("checksum error");
    flushRFIDBuffer();
  }else if (x == 0) {
    Serial.println("empty");
    //Why flushing at 0 is risky:
    /*
      Serial data arrives one byte at a time. If the reader has sent 5 bytes
      and your code runs, rfid.available() is 5. Your function returns 0 
      because it needs 14 bytes. If you flush now, you delete those 5 bytes. 
      The reader finishes sending the remaining 9 bytes, but since you deleted 
      the first 5, the packet is now broken.
     */
  }else {
    Serial.println(x);
    flushRFIDBuffer();
  }
  delay(2000);
  digitalWrite(LED, LOW);
  delay(2000);
}

// void verifyAndPrint(char* data) {
//   uint8_t calculated_checksum = 0;
  
//   // 1. Convert 10 ASCII chars to 5 hex bytes and XOR them
//   for (int i = 0; i < 10; i += 2) {
//     calculated_checksum ^= hexToByte(data[i], data[i+1]);
//   }

//   // 2. Convert the 2 received checksum chars to 1 hex byte
//   uint8_t received_checksum = hexToByte(data[10], data[11]);

//   // 3. Compare results
//   if (calculated_checksum == received_checksum) {
//     Serial.print("Tag ID (Valid): ");
//     Serial.println(convertHexIdToDecId(data));
//   } else {
//     Serial.println("Checksum Error! Data corrupted.");
//   }
// }

// //converts the HEX id to Decimal value
// unsigned long convertHexIdToDecId(const char* data) {
//   char uidHex[9];
//   memcpy(uidHex, data + 2, 8);
//   uidHex[8] = '\0';
//   Serial.println(uidHex);   // HEX
//   return strtoul(uidHex, NULL, 16);  // DEC
// }

// // Helper: Converts two ASCII hex chars (e.g. 'A', 'F') to one byte (0xAF)
// uint8_t hexToByte(char high, char low) {
//   return (nibble(high) << 4) | nibble(low);
// }

// uint8_t nibble(char c) {
//   if (c >= '0' && c <= '9') return c - '0';
//   if (c >= 'A' && c <= 'F') return c - 'A' + 10;
//   return 0;
// }

