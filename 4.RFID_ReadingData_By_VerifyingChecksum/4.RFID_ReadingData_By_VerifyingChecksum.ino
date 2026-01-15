#include <SoftwareSerial.h>

#define RFID_RX D6 
#define RFID_TX D5 

SoftwareSerial rfid(RFID_RX, RFID_TX);

void setup() {
  Serial.begin(9600);
  rfid.begin(9600);
  Serial.println("\nESP8266 RFID Reader with Checksum Verification Ready...");
}

void loop() {
  // RDM6300 sends 14 bytes: [Start:0x02] [Data:10 chars] [Checksum:2 chars] [End:0x03]
  if (rfid.available() >= 14) {
    if (rfid.read() == 0x02) { // Found Start Byte
      char buffer[13]; // To hold 10 data chars + 2 checksum chars + null
      rfid.readBytes(buffer, 12);
      uint8_t endByte = rfid.read();

      if (endByte == 0x03) {
        verifyAndPrint(buffer);
      }
    }
  }
}

void verifyAndPrint(char* data) {
  uint8_t calculated_checksum = 0;
  
  // 1. Convert 10 ASCII chars to 5 hex bytes and XOR them
  for (int i = 0; i < 10; i += 2) {
    calculated_checksum ^= hexToByte(data[i], data[i+1]);
  }

  // 2. Convert the 2 received checksum chars to 1 hex byte
  uint8_t received_checksum = hexToByte(data[10], data[11]);

  // 3. Compare results
  if (calculated_checksum == received_checksum) {
    Serial.print("Tag ID (Valid): ");
    Serial.println(convertHexIdToDecId(data));
  } else {
    Serial.println("Checksum Error! Data corrupted.");
  }
}

//converts the HEX id to Decimal value
unsigned long convertHexIdToDecId(const char* data) {
  char uidHex[9];
  memcpy(uidHex, data + 2, 8);
  uidHex[8] = '\0';
  Serial.println(uidHex);   // HEX
  return strtoul(uidHex, NULL, 16);  // DEC
}

// Helper: Converts two ASCII hex chars (e.g. 'A', 'F') to one byte (0xAF)
uint8_t hexToByte(char high, char low) {
  return (nibble(high) << 4) | nibble(low);
}

uint8_t nibble(char c) {
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'A' && c <= 'F') return c - 'A' + 10;
  return 0;
}







// #include <SoftwareSerial.h>

// // For ESP8266 (NodeMCU), D5 is GPIO14, D6 is GPIO12
// #define RFID_RX D6 
// #define RFID_TX D5 // Not used, but required by SoftwareSerial

// SoftwareSerial rfid(RFID_RX, RFID_TX);

// void setup() {
//   Serial.begin(9600); // Standard ESP8266 baud rate
//   rfid.begin(9600);      // RDM6300 is always 9600
//   Serial.println("\nESP8266 RFID Reader Ready...");
// } 

// void loop() {
//   if (rfid.available() >= 14) {
//     if (rfid.read() == 0x02) { // Verify Start Byte
//       Serial.print("Tag ID: ");
//       for (int i = 0; i < 10; i++) {
//         char c = rfid.read();
//         Serial.print(c); // Print the 10-digit ID
//       }
      
//       Serial.println();

//       Serial.print("Checksum + end byte: ");
//       // Read the remaining 3 bytes (checksum + end byte) to clear buffer
//       for (int i = 0; i < 3; i++) {
//         rfid.read(); 
//         char c = rfid.read();
//         Serial.print(c); // Print checksum + end byte
//       }
//       Serial.println();
//     }
//   }
// }
