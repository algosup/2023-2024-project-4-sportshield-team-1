#include "MotionManager.h"

MotionManager::MotionManager() : imu(Wire, 0x6A), threshold(1.0) {
}

void MotionManager::begin() {
    if (!imu.begin()) {
        Serial.println("Failed to initialize IMU!");
        while (1);
    }
    imu.setAccelRange(LSM6DS3::RANGE_2_G); // Set accelerometer range
}

bool MotionManager::checkMotion() {
    return isMotionDetected();
}

float MotionManager::readAccelerationX() {
    return imu.readFloatAccelX();
}

float MotionManager::readAccelerationY() {
    return imu.readFloatAccelY();
}

float MotionManager::readAccelerationZ() {
    return imu.readFloatAccelZ();
}

bool MotionManager::isMotionDetected() {
    // Check if the acceleration in any direction exceeds the threshold
    if (abs(readAccelerationX()) > threshold || abs(readAccelerationY()) > threshold || abs(readAccelerationZ()) > threshold) {
        return true;
    }
    return false;
}
