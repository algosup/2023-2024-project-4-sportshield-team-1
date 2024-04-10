#ifndef MotionManager_h
#define MotionManager_h

#include <Arduino.h>
#include <Wire.h>
#include <LSM6DS3.h>

class MotionManager {
public:
    MotionManager(); // Constructor
    void begin(); // Initializes the IMU sensor
    bool checkMotion(); // Checks for any motion. Returns true if motion is detected
    float readAccelerationX(); // Reads acceleration in X direction
    float readAccelerationY(); // Reads acceleration in Y direction
    float readAccelerationZ(); // Reads acceleration in Z direction
    bool isMotionDetected(); // Returns true if motion is detected based on predefined thresholds

private:
    LSM6DS3 imu; // IMU sensor object
    float threshold; // Threshold for motion detection
};

#endif
