#include "GPSManager.h"

GPSManager::GPSManager() : GPS(&GPSSerial) {
    latitude = 0.0;
    longitude = 0.0;
    lastNMEA = "";
}

void GPSManager::begin() {
    GPS.begin(9600); // Initialize GPS at specified baud rate
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); // Only RMC (minimum recommended) and GGA (fix data) sentences
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
    GPSSerial.println(PMTK_Q_RELEASE); // Ask for the firmware version
}

bool GPSManager::updateLocation() {
    if (GPS.newNMEAreceived()) {
        if (GPS.parse(GPS.lastNMEA())) { // Parses the latest NMEA sentence
            latitude = GPS.latitudeDegrees;
            longitude = GPS.longitudeDegrees;
            lastNMEA = GPS.lastNMEA();
            return true;
        }
    }
    return false;
}

float GPSManager::getLatitude() {
    return latitude;
}

float GPSManager::getLongitude() {
    return longitude;
}

String GPSManager::getLastNMEA() {
    return lastNMEA;
}
