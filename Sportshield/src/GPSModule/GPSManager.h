#ifndef GPSManager_h
#define GPSManager_h

#include <Arduino.h>
#include <Adafruit_GPS.h>

// GPS serial connection
#define GPSSerial Serial1

class GPSManager {
public:
    GPSManager(); // Constructor
    void begin(); // Initializes the GPS module
    bool updateLocation(); // Updates and checks if a new location data is available
    float getLatitude(); // Returns the current latitude
    float getLongitude(); // Returns the current longitude
    String getLastNMEA(); // Returns the last NMEA sentence received
    
private:
    Adafruit_GPS GPS; // GPS object
    float latitude; // Current latitude
    float longitude; // Current longitude
    String lastNMEA; // Last NMEA sentence received
};

#endif
