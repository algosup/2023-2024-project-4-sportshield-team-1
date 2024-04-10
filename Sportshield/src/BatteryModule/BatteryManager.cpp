#include "BatteryManager.h"

BatteryManager::BatteryManager(int batteryPin) : _batteryPin(batteryPin) {
}

float BatteryManager::readBatteryLevel() {
    float voltage = readVoltage();
    float level = map(voltage, 3.2, 4.2, 0, 100); // Assuming 3.2V as min and 4.2V as max battery voltage
    level = constrain(level, 0, 100); // Ensure the level is between 0 and 100
    return level;
}

void BatteryManager::checkBatteryStatus() {
    float level = readBatteryLevel();
    if (level < 20) {
        // Implement low battery warning or actions
        Serial.println("Warning: Low Battery!");
    }
}

float BatteryManager::readVoltage() {
    int sensorValue = analogRead(_batteryPin);
    return sensorValue * (4.2 / 1023.0); // Convert analog reading to voltage
}
