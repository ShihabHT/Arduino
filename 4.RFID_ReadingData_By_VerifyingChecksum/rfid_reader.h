#ifndef RFID_READER_H
#define RFID_READER_H

#include <SoftwareSerial.h>

#define RFID_RX D6 
#define RFID_TX D5 

SoftwareSerial rfid(RFID_RX, RFID_TX);

/**
 * To use this header, begin RFID (rfid.begin(9600)) in setup and call the gerRFIDTag()
 * Checks for RFID data. 
 * Returns the Decimal ID as an unsigned long if successful, 
 * or -1 if no tag is read or checksum fails.
 */
unsigned long getRFIDTag() {
  // RDM6300 sends 14 bytes: [Start:0x02] [Data:10 chars] [Checksum:2 chars] [End:0x03]
  if (rfid.available() >= 14) {
    if (rfid.read() == 0x02) { // Found Start Byte
      char buffer[13]; // To hold 10 data chars + 2 checksum chars + null
      rfid.readBytes(buffer, 12);
      uint8_t endByte = rfid.read();

      if (endByte == 0x03) {
        uint8_t calculated_checksum = 0;

        // 1. Convert 10 ASCII chars to 5 hex bytes and XOR them
        for (int i = 0; i < 10; i += 2) {
          calculated_checksum ^= hexToByte(buffer[i], buffer[i + 1]);
        }

        // 2. Convert the 2 received checksum chars to 1 hex byte
        uint8_t received_checksum = hexToByte(buffer[10], buffer[11]);

        // 3. Compare results
        if (calculated_checksum == received_checksum) {
          Serial.print("Tag ID (Valid): ");
          return convertHexIdToDecId(buffer);
        } else {
          return -1; // returned if data checksum error occurs
        }
      }
    }
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

