#include <Arduino.h>
#include <LSM6DS3.h>
 
#include "BluetoothModule/BluetoothManager.h"
#include "GPSModule/GPSManager.h"
#include "BatteryModule/BatteryManager.h"
#include "NFCModule/NFCManager.h"
#include "AlarmModule/AlarmManager.h"
#include "NetworkModule/NetworkManager.h"
#include "MotionModule/MotionManager.h"

// Define pins and other constants here
#define BATTERY_PIN A0
#define BUZZER_PIN 9
// Define other pins and constants for GPS, NFC, GSM, and BLE

// Initialize module objects here
BluetoothManager bluetoothManager; // Initialize with appropriate parameters if needed
GPSManager gpsManager; // Initialize with appropriate parameters if needed
BatteryManager batteryManager(BATTERY_PIN); // Assuming battery level is read from A0
NFCManager nfcManager; // Initialize with appropriate pins for SDA, SCL
AlarmManager alarmManager(BUZZER_PIN); // Assuming buzzer is connected to pin 9
NetworkManager networkManager("your_apn", "your_user", "your_pass", Serial1); // Replace with your GSM module settings

void setup() {
    Serial.begin(9600);
    if (!myIMU.begin()) {
        Serial.println("Failed to initialize IMU!");
        while (1);
    }

    // Initialize modules
    bluetoothManager.begin();
    gpsManager.begin();
    batteryManager.begin(); // Assuming there's a begin method to initialize things
    nfcManager.begin();
    alarmManager.begin(); // Assuming there's a begin method for setup
    networkManager.begin();
}

void loop() {
    // Motion detection
    MotionData = getMotionData(); // Implement this based on your IMU sensor's library
    RotationData = getRotationData(); // Implement this based on your IMU sensor's library
  
    // Serial command handling
    handleSerialCommands();

    // NFC Tag Detection and Processing
    handleNFCTags();

    // Check and handle motion detection scenarios
    handleMotionDetection();

    // Bluetooth and power management based on motion detection
    manageBluetoothAndPower();

    // Delay for loop iteration as needed
    delay(10);
}

void processSerialCommand(String command) {
    if (command.equalsIgnoreCase("unlock_mode")) {
        if (Config.isActivate) {
            Serial.println(F("Unlocking the hardware..."));
            Config.isActivate = false;
            interruptBuzzer(); 
        } else {
            Serial.println(F("Hardware already unlocked..."));
        }
    } else if (command.equalsIgnoreCase("activate_mode")) {
        if (!Config.isActivate) {
            Serial.println(F("Locking the hardware..."));
            Config.isActivate = true;
            startBuzzer();
        } else {
            Serial.println(F("Hardware already locked..."));
        }
    } else if (command.equalsIgnoreCase("check_motion")) {
        if (MotionDetect) {
            Serial.println(F("Motion detected."));
        } else {
            Serial.println(F("No motion detected."));
        }
    } else if (command.equalsIgnoreCase("check_battery")) {
        float batteryLevel = getBatteryLevel();
        Serial.print(F("Battery Level: "));
        Serial.print(batteryLevel);
        Serial.println(F("V"));
    } else if (command.equalsIgnoreCase("check_voltage")) {
        float voltage = getVoltage();
        Serial.print(F("Voltage: "));
        Serial.print(voltage);
        Serial.println(F("V"));
    } else {
        Serial.println(F("Unknown command."));
    }
}

void handleSerialCommands() {
    static String inputBuffer = "";
    if (Serial.available() > 0) {
        char incomingChar = Serial.read();
        if (incomingChar == '\n' || incomingChar == '\r') {
            inputBuffer.trim();
            if (inputBuffer.equalsIgnoreCase("unlock_mode")) {
                if (Config.isActivate) {
                    Serial.println(F("Unlocking the hardware..."));
                    Config.isActivate = false;
                    interruptBuzzer(); 
                } else {
                    Serial.println(F("Hardware already unlocked..."));
                }
            } 
            inputBuffer = ""; // Clear the buffer after processing the command
        } else {
            inputBuffer += incomingChar; // Append the incoming character to the buffer
        }
    }
}

void handleMotionDetection() {
    const float BigMT = 1.0, SmallMT = 0.5, BigRT = 1.0, SmallRT = 0.5;
    static bool MotionBig = false, MotionSmall = false;

    // Process motion and rotation data
    if (MotionData > BigMT || RotationData > BigRT) {
        MotionBig = true;
        MotionSmall = false;
        handleBigMotion();
    } else if (!MotionBig && (MotionData > SmallMT || RotationData > SmallRT)) {
        MotionSmall = true;
        handleSmallMotion();
    }
}

void handleNFCTags() {
    uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0}; // Buffer to store the UID
    uint8_t uidLength; // Length of the UID

    bool success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
    if (success) {
        Serial.println("Found an NFC tag.");
        String uidStr = convertUidToString(uid, uidLength);
        if (uidStr.equalsIgnoreCase("04A2B3C4D5")) { // Authorized UID
            handleAuthorizedTag();
        } else {
            Serial.println("Unauthorized NFC Tag.");
        }
    }
}

String convertUidToString(uint8_t* uid, uint8_t uidLength) {
    String uidStr = "";
    for (uint8_t i = 0; i < uidLength; i++) {
        if(uid[i] < 0x10) uidStr += "0"; // Leading zero
        uidStr += String(uid[i], HEX);
    }
    uidStr.toUpperCase();
    return uidStr;
}

void handleAuthorizedTag() {
    if (!Config.isActivate) {
        Serial.println(F("Unlocking the hardware..."));
        Config.isActivate = true;
        startBuzzer();
    } else {
        Serial.println(F("Hardware already unlocked..."));
    }
}

void manageBluetoothAndPower() {
    static unsigned long lastMotionDetectedTime = 0;
    if (MotionDetect) {
        lastMotionDetectedTime = millis();
        if (!BLE_activated) {
            BLE_activated = true;
            ble_setup();
        }
    }
    // Turn off BLE after a timeout to save power if no motion detected
    if (BLE_activated && millis() - lastMotionDetectedTime > TIMEOUT) {
        BLE_activated = false;
        BLE.end();
    }
}

float getMotionData() {
    float ax = myIMU.readFloatAccelX();
    float ay = myIMU.readFloatAccelY();
    float az = myIMU.readFloatAccelZ();

    // Calculate the magnitude of the acceleration vector
    float aMagnitude = sqrt(ax * ax + ay * ay + az * az);

    return aMagnitude;
}

float getRotationData() {
    float gx = myIMU.readFloatGyroX();
    float gy = myIMU.readFloatGyroY();
    float gz = myIMU.readFloatGyroZ();

    // Calculate the magnitude of the rotation vector
    float gMagnitude = sqrt(gx * gx + gy * gy + gz * gz);

    return gMagnitude;
}

void handleBigMotion() {
    if (!Config.isActivate) {
        Serial.println(F("Motion detected. Locking the hardware..."));
        Config.isActivate = true;
        startBuzzer();
    }
}

void handleSmallMotion() {
    if (Config.isActivate) {
        Serial.println(F("Small motion detected. Unlocking the hardware..."));
        Config.isActivate = false;
        interruptBuzzer();
    }
}

float getBatteryLevel() {
    return batteryManager.getVoltage();
}

float getVoltage() {
    return batteryManager.getVoltage();
}

void startBuzzer() {
    alarmManager.start();
}

void interruptBuzzer() {
    alarmManager.stop();
}

void ble_setup() {
    // Initialize BLE module
    BLE.begin();
    BLE.setLocalName("SportShield");
    BLE.setAdvertisedService(service);
    service.addCharacteristic(characteristic);
    BLE.addService(service);
    BLE.advertise();
}

void ble_loop() {
    BLE.poll();
}


