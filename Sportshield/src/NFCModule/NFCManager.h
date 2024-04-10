#ifndef NFCManager_h
#define NFCManager_h

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PN532.h>

class NFCManager {
public:
    NFCManager(uint8_t sda, uint8_t scl); // Constructor for I2C communication
    void begin(); // Initializes the NFC module
    bool scanForTag(); // Scans for NFC tags and returns true if a tag is found
    String readTagUID(); // Reads the UID of the scanned tag
    
private:
    Adafruit_PN532 nfc; // NFC object
    bool isTagPresent; // Indicates if a tag is present
    String tagUID; // Stores the UID of the tag
};

#endif
