#ifndef BluetoothManager_h
#define BluetoothManager_h

#include <Arduino.h>
#include <ArduinoBLE.h>

class BluetoothManager {
public:
    BluetoothManager(); // Constructor
    void begin(); // Initializes the Bluetooth module
    bool connectDevice(); // Attempts to connect to the device
    bool readMACAddress(String &macAddress); // Reads the MAC address of the device
    bool activateAntiTheft(bool activate); // Activates or deactivates the anti-theft system
    bool unlockDevice(); // Unlocks the device
    
private:
    void setupBLE(); // Private method to setup BLE characteristics and services
    BLEService *antiTheftService; // BLE service for anti-theft functionality
    BLEStringCharacteristic *macAddressCharacteristic; // Characteristic for MAC address
    BLEIntCharacteristic *activationCharacteristic; // Characteristic for activation/deactivation
    BLEIntCharacteristic *unlockCharacteristic; // Characteristic for unlocking the device
};

#endif
