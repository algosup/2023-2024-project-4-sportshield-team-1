#ifndef BatteryManager_h
#define BatteryManager_h

#include <Arduino.h>

class BatteryManager {
public:
    BatteryManager(int batteryPin); // Constructor with battery pin
    float readBatteryLevel(); // Reads and returns the battery level as a percentage
    void checkBatteryStatus(); // Checks the battery status and performs actions based on level
    
private:
    int _batteryPin; // Analog pin used to read battery level
    float readVoltage(); // Reads the battery voltage
};

#endif
