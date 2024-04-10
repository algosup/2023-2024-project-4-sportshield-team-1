#define TIMER_INTERRUPT_DEBUG 0
#define _TIMERINTERRUPT_LOGLEVEL_ 0
#include "NRF52_MBED_TimerInterrupt.h"
#include "NRF52_MBED_ISR_Timer.h"
#include <Arduino.h>
// BLE
#include <ArduinoBLE.h>
#include "struct.h"
// IMU
#include <LSM6DS3.h>
#include <Wire.h>
// GPS
#include <Adafruit_GPS.h>
// SIM
#include "SIM800L.h"
// NFC
#include <NfcAdapter.h>
#include <PN532/PN532/PN532.h>

#include <SPI.h>
#include <PN532/PN532_SPI/PN532_SPI.h>
#include <PN532/PN532/PN532.h>
#include <NfcAdapter.h>

PN532_SPI pn532spi(SPI, 10);
NfcAdapter nfc = NfcAdapter(pn532spi);

//---------------- GLOBAL VARIABLES -----------------------------
myConfig Config;
bool isAuthenticate = false;
// Timer
#define HW_TIMER_INTERVAL_MS 1
NRF52_MBED_Timer ITimer(NRF_TIMER_3);
NRF52_MBED_ISRTimer ISR_Timer;
#define TIMER_INTERVAL_120S 120000L
// BLE
BLEService PasswordService("19B10000-E8F2-537E-4F6C-D104768A1213");  // Bluetooth® Low Energy Service
BLEService ConfigService("19B10000-E8F2-537E-4F6C-D104768A1214");

BLEShortCharacteristic PasswordCharacteristic("19B10000-E8F2-537E-4F6C-D104768A1213", BLEWrite);  // Bluetooth® Low Energy Characteristic
BLEStringCharacteristic NameCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite, 20);
BLEStringCharacteristic MACCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1217", BLERead, 20);
BLEBooleanCharacteristic ActivationCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1215", BLERead | BLEWrite);
BLEBooleanCharacteristic UnlockCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1216", BLEWrite);

BLEDescriptor PasswordDescriptor("2901", "Password");  // Bluetooth® Low Energy Descriptor
BLEDescriptor NameDescriptor("2901", "Lovely Team 1");
BLEDescriptor ActivationDescriptor("2901", "Lock/Activation");
BLEDescriptor UnlockDescriptor("2901", "Unlock/Disactivation");
BLEDescriptor MACDescriptor("2901", "MAC Address");

bool BLE_activated = true;  //true if the bluetooth is activated
uint32_t tim_connec = 0;    // time in ms or we start to activate the bluetooth following a detection of movement


//IMU : LSM6DS3
LSM6DS3 imu(I2C_MODE, 0x6A);  //I2C device address 0x6A
uint32_t timer_imu = millis();
bool MotionBig = false;
bool MotionSmall = false;
bool MotionDetect = false;

// GPS PA1010D
Adafruit_GPS GPS(&Serial1);
bool start_gps = false;
bool position_acquired = false;
uint32_t timer = millis();
#define GPS_WKUP_PIN D8

// SIM800L GSM 2G Module
UART Serial2(D0, D1, NC, NC);
#define SIM800_RST_PIN A5
#define SIM800_DTR_PIN A5
#define TIME_OUT_MS_BLE_ACT 5000  // 300s 300000 times in ms or bluetooth enabled to allow connection following motion detection. (value 5000 for 5s tests)
SIM800L* sim800l;
bool send_position = false;
bool send_move = false;

// // Buzzer
const int buzzerPin = D2;
void PulseBuzzer(int repetitions, unsigned long durationOn, unsigned long durationOff);
unsigned long previousMillis = 0;
int currentRep = 0;

//Electroaimant
const int aimantPin = D3;

// Set a threshold to determine a "small" or "big" movement

float SmallMT = 20.0;  //     SmallMotionThreshold
float BigMT = 150.0;   //    BigMotionThreshold

float SmallRT = 20.0;  //     SmallRotationThreshold
float BigRT = 125.0;   //     BigRotationThreshold

//batterie
#define VBAT_ENABLE 14
float getBatteryVoltage();

float MotionData;
float RotationData;

unsigned long StartCoolDown = 0;  //check point for millis aided cooldown

bool interruptFlag = false;

// NFC 
#define SDA_PIN 0
#define SCL_PIN 1
#define PN532_IRQ   (2)
#define PN532_RESET (3)  // Not connected by default on the NFC Shield

//-------------------------------- SETUP ----------------------------------------
void setup() {
  pinMode(buzzerPin, OUTPUT);  // setup for buzzer
  digitalWrite(buzzerPin, HIGH);
  delay(1000);
  digitalWrite(buzzerPin, LOW);
  Serial.println("buzzer");

  pinMode(aimantPin, OUTPUT);  //setup electro-aimant
  digitalWrite(aimantPin, HIGH);
  delay(1000);
  digitalWrite(aimantPin, LOW);
  Serial.println("electro");

  //debug led initialization
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LEDR, LOW);

  // power bridge control
  pinMode(D4, OUTPUT);
  digitalWrite(D4, HIGH);

  // power battery control with the transistor
  pinMode(D9, OUTPUT);
  digitalWrite(D9, HIGH);

  // battery charging enable with high current 100mA > 50mA
  pinMode(P0_13, OUTPUT);
  digitalWrite(P0_13, LOW);

  Serial.begin(115200);
  if (!Serial) delay(1000);
  Serial.println("BLE Antivol Peripheral");

  // Timer
  if (ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, TimerHandler))  // Interval in microsecs
  {
    Serial.print(F("Starting ITimer OK, millis() = "));
    Serial.println(millis());
  }
  ISR_Timer.setInterval(TIMER_INTERVAL_120S, GPS_ISR);

  ble_setup();
  Serial.println(" ble_setup");
  imu_setup();
  Serial.println(" imu_setup");
  gps_setup();
  Serial.println(" gps_setup");
  Serial2.begin(9600);
  delay(100);
  sim800l = new SIM800L((Stream*)&Serial2, SIM800_RST_PIN, 200, 512);
  pinMode(SIM800_DTR_PIN, OUTPUT);
  delay(1000);
  //sim_setup();
  //Serial.println("SIM SETUP");

  analogReadResolution(ADC_RESOLUTION);  //setup battery reading
  pinMode(PIN_VBAT, INPUT);
  pinMode(VBAT_ENABLE, OUTPUT);
  digitalWrite(VBAT_ENABLE, LOW);

  Serial.println("end setup ");
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, LOW);
  Time();

  Serial.print("V Bat: ");
  Serial.println(getBatteryVoltage());
  Serial.print("Battery Level: ");
  Serial.println(getBatteryLevel());

  // NFC
  nfc_setup();
  Serial.println("NFC setup");
}

//-------------------------------- LOOP ----------------------------------------
void loop() {
  // Motion detection
  MotionData = getMotionData();
  RotationData = getRotationData();
  
  // Serial command handling
  static String inputBuffer = ""; 
  static unsigned long lastInputTime = 0; 

  if (Serial.available() > 0) {
    char incomingChar = Serial.read();

    if (incomingChar == '\n' || incomingChar == '\r') {
      inputBuffer.trim(); 
      
      if (inputBuffer.equalsIgnoreCase("unlock_mode")) {
        if (Config.isActivate == true) {
          Serial.println(F("Unlocking the hardware..."));
          Config.isActivate = false;
          interruptBuzzer();
        } else {
          Serial.println(F("Hardware already unlocked..."));
        }
      } else if (inputBuffer.equalsIgnoreCase("activate_mode")) {
        if (Config.isActivate == false) {
          Serial.println(F("Activating the hardware..."));
          Config.isActivate = true;
        } else {
          Serial.println(F("Hardware is already unlocked..."));
        }
      } else if (inputBuffer.equalsIgnoreCase("check_battery")) {
        Serial.print("Battery Level: ");
        Serial.println(getBatteryLevel());
      } else if (inputBuffer.equalsIgnoreCase("check_voltage")) {
        Serial.print("Battery Voltage: ");
        Serial.println(getBatteryVoltage());
      } else {
        Serial.println(F("Unknown command."));
      }

      inputBuffer = ""; // Clear the buffer after processing the command
    } else {
      inputBuffer += incomingChar; // Append the incoming character to the buffer
      lastInputTime = millis(); // Update the last input time
    }
  }

  uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0};  // Buffer to store the UID
  uint8_t uidLength;                      // Length of the UID (7 bytes for UID of ISO14443A cards)

  bool success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    Serial.println("Found an NFC tag.");
    
    // Convert UID array to String for easy comparison and logging
    String uidStr;
    for (uint8_t i = 0; i < uidLength; i++) {
      uidStr += String(uid[i], HEX);
    }

    Serial.print("UID: ");
    Serial.println(uidStr);

    // Assuming '04A2B3C4D5' is the UID of the authorized tag
    String authorizedUid = "04A2B3C4D5"; // Example UID, replace with the actual authorized UID
    if (uidStr.equalsIgnoreCase(authorizedUid)) {
      Serial.println("Authorized NFC Tag Detected!");

      // Example: Activate or unlock device based on its current state
      if (!Config.isActivate) {
        Serial.println("Activating the device...");
        Config.isActivate = true;
        // Add your code here to handle activation
      } else {
        Serial.println("Unlocking the device...");
        // Add your code here to handle unlocking
      }
    } else {
      Serial.println("Unauthorized NFC Tag.");
    }

    if (nfc.tagPresent()) {
        NfcTag tag = nfc.read();
        Serial.print("Tag type: ");
        Serial.println(tag.getTagType());
        Serial.print("UID: ");
        Serial.println(tag.getUidString());
    }
  }

  if (Config.isActivate) {  //alarm enalbled
    activateGPS();

    if (MotionData > BigMT || RotationData > BigRT) {  //Big motion detection
      if (MotionData > BigMT) {
        Serial.print("Motion detected : ");
        Serial.println(MotionData);
      } else {
        Serial.print("Rotation detected : ");
        Serial.println(RotationData);
      }
      MotionBig = true;
      MotionSmall = false;
      send_move = true;

    } else if ((MotionBig == false) && (MotionData > SmallMT || RotationData > SmallRT)) {  //Small motion detection
      if (MotionData > SmallMT) {
        Serial.print(" Small motion: ");
        Serial.println(MotionData);
      } else {
        Serial.print("Small rota : ");
        Serial.println(RotationData);
      }
      MotionSmall = true;
    }
  }

  if (MotionBig) {
    if(Config.isActivate == false){

    } else if (Config.isActivate == true && MotionBig == true){
      PulseBuzzer(5, 500, 1000);
    }
    //sending positions & shock notif via SIM module
  }

  if (MotionSmall) {
    PulseBuzzer(3, 100, 100);  // repetitions, DurationOn , DurationOff
  }

  MotionDetect = true;
  if ((MotionData > SmallMT) || (RotationData > SmallRT)) {
    if (MotionData > SmallMT) {
      Serial.print("WAKE UP : ");
      Serial.println(MotionData);
    } else {
      Serial.print("WAKE UP Rota: ");
      Serial.println(RotationData);
    }
  }
  //if a mvt is detected and bluetooth is disabled bluetooth activation
  if (MotionDetect == true) {
    tim_connec = millis();
    MotionDetect = false;
    if (BLE_activated == false) {
      BLE_activated = true;
      Serial.println("MVT_detect->setup");
      ble_setup();
    }
  }

  //bluetooth actived when we are interacting with the module or when the alarm is on
  if ((BLE_activated == true) || (Config.isActivate)) {
    BLE.poll();  //communication autorisé
  }

  //at the end of the time during which the lock has not moved, if bluetooth is activated, and the lock is not in activation mode then it is turned off to save the battery
  if ((millis() - tim_connec > TIME_OUT_MS_BLE_ACT) && (BLE_activated == true) && (Config.isActivate != 1)) {
    BLE_activated = false;
    Serial.println("timeout->BLE_END");
    BLE.end();
  }

  //capture clocked GPS data
GPS.read();
//   if (GPS.newNMEAreceived()) {
//     Serial.print(GPS.lastNMEA());    // this also sets the newNMEAreceived() flag to false
//     if (!GPS.parse(GPS.lastNMEA()))  // this also sets the newNMEAreceived() flag to false
//       Serial.println("fail to parse");
//     ;  // we can fail to parse a   sentence in which case we should just wait for another
//   }

//   if (GPS.fix && position_acquired == false) {  // if location detected
//     Serial.println("fix + false");
//     position_acquired = true;
//     GPS.fix = 0;
//     digitalWrite(GPS_WKUP_PIN, LOW);
//     GPS.sendCommand("$PMTK225,4*2F");  // send to backup mode
//   }

//   if (send_move) {  //sending of positions via SIM module
//     Serial.println("Envoi detection mouvement");
//     sim800l->setupGPRS("iot.1nce.net");
//     sim800l->connectGPRS();
//     String Route = "http://elderzia.fr/sendNotfication.php/" + BLE.address();
//     String RouteCoord = "http://elderzia.fr/updateCoordinate/" + BLE.address();
//     String str = "{\"latitude\": \" " + convertDMMtoDD(String(float(GPS.latitude), 4)) + "\", \"longitude\":\"" + convertDMMtoDD(String(float(GPS.longitude), 4)) + "\"}";
//     String bat = "{\"latitude\": \" " + convertDMMtoDD(String(float(GPS.latitude), 4)) + "\", \"longitude\":\"" + convertDMMtoDD(String(float(GPS.longitude), 4)) + "\", \"batterie\":\"" + String(getBatteryVoltage()) + "\"}";
//     char position[200];
//     char posbat[200];
//     str.toCharArray(position, str.length() + 1);
//     //Serial.println(str);
//     bat.toCharArray(posbat, bat.length() + 1);
//     Serial.println(posbat);
//     char direction[200];
//     char directionCoord[200];
//     Route.toCharArray(direction, Route.length() + 1);
//     RouteCoord.toCharArray(directionCoord, RouteCoord.length() + 1);
//     sim800l->doPost(direction, "application/json", position, 10000, 10000);
//     sim800l->doPost(directionCoord, "application/json", posbat, 10000, 10000);
//     sim800l->disconnectGPRS();
//     send_move = false;
//   }

//   if (send_position) {  //regular sending of positions via SIM module
//     Serial.println("Envoi regulier position");
//     sim800l->setupGPRS("iot.1nce.net");
//     sim800l->connectGPRS();
//     String RouteCoord = "http://elderzia.fr/updateCoordinate/" + BLE.address();
//     String bat = "{\"latitude\": \" " + convertDMMtoDD(String(float(GPS.latitude), 4)) + "\", \"longitude\":\"" + convertDMMtoDD(String(float(GPS.longitude), 4)) + "\", \"batterie\":\"" + String(getBatteryVoltage()) + "\"}";
//     char posbat[200];
//     bat.toCharArray(posbat, bat.length() + 1);
//     Serial.println(posbat);
//     Serial.println(RouteCoord);
//     char directionCoord[200];
//     RouteCoord.toCharArray(directionCoord, RouteCoord.length() + 1);
//     sim800l->doPost(directionCoord, "application/json", posbat, 10000, 10000);
//     sim800l->disconnectGPRS();
//     send_position = false;
//   }
}

//------------- SETUP FUNCTIONS ------------------------------
void ble_setup(void) {
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");
    while (1)  // set a reset in this case? risk of card crash?
      ;
  }
  // set advertised local name and service UUID:
  BLE.setLocalName("L'adorable Team 1");
  BLE.setDeviceName("L'adorable Team 1");
  BLE.setAdvertisedService(PasswordService);
  // add descriptors
  PasswordCharacteristic.addDescriptor(PasswordDescriptor);
  NameCharacteristic.addDescriptor(NameDescriptor);
  ActivationCharacteristic.addDescriptor(ActivationDescriptor);
  UnlockCharacteristic.addDescriptor(UnlockDescriptor);
  MACCharacteristic.addDescriptor(MACDescriptor);
  // add the characteristic to the service
  PasswordService.addCharacteristic(PasswordCharacteristic);
  ConfigService.addCharacteristic(NameCharacteristic);
  ConfigService.addCharacteristic(ActivationCharacteristic);
  ConfigService.addCharacteristic(UnlockCharacteristic);
  ConfigService.addCharacteristic(MACCharacteristic);
  // add service
  BLE.addService(PasswordService);
  BLE.addService(ConfigService);
  // set the initial value for the characeristic:
  PasswordCharacteristic.writeValue(0);
  NameCharacteristic.writeValue("\n");
  ActivationCharacteristic.writeValue(false);
  UnlockCharacteristic.writeValue(false);
  MACCharacteristic.writeValue(BLE.address());
  //set event handler
  BLE.setEventHandler(BLEConnected, onConnect);
  BLE.setEventHandler(BLEDisconnected, onDisconnect);
  PasswordCharacteristic.setEventHandler(BLEWritten, onWritePassword);
  NameCharacteristic.setEventHandler(BLEWritten, onWriteName);
  NameCharacteristic.setEventHandler(BLERead, onReadName);
  ActivationCharacteristic.setEventHandler(BLEWritten, onWriteActivation);
  ActivationCharacteristic.setEventHandler(BLERead, onReadActivation);
  UnlockCharacteristic.setEventHandler(BLEWritten, onWriteUnlock);
  // start advertising
  BLE.advertise();
}

void imu_setup(void) {
  if (imu.begin() != 0) {
    Serial.println("Device error");
  } else {
    Serial.println("Accelerometer launched");
  }
}

void gps_setup(void) {
  pinMode(GPS_WKUP_PIN, OUTPUT);
  digitalWrite(GPS_WKUP_PIN, LOW);
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand("$PMTK225,4*2F");  // send to backup mode
  // GPS.sendCommand("$PMTK225,8*23");   // send to Always Locate backup mode
  // GPS.sendCommand("$PMTK225,9*22");   // send to Always Locate standby mode
  // GPS.sendCommand("$PMTK225,2,4000,15000,24000,90000*16");  // send to periodic standby mode
  // GPS.sendCommand("$PMTK161,0*28");   // send to standby mode
}

void sim_setup(void) {
  while (!sim800l->isReady()) {
    Serial.println(F("Problem to initialize AT command, retry in 1 sec"));
    digitalWrite(LEDR, !digitalRead(LEDR));
    delay(1000);
  }
  sim800l->enableEchoMode();
  sim800l->setupGPRS("iot.1nce.net");

  uint8_t signal = sim800l->getSignal();
  while (signal <= 0) {
    delay(1000);
    signal = sim800l->getSignal();
    Serial.println(F("Waiting signal..."));
  }
  Serial.println(String(signal));
  NetworkRegistration network = sim800l->getRegistrationStatus();
  // while (network != REGISTERED_HOME && network != REGISTERED_ROAMING) {
  //   delay(1000);
  //   network = sim800l->getRegistrationStatus();
  //   Serial.print(network + " ");
  //   Serial.println(F("Problem to register, retry in 1 sec"));
  //   digitalWrite(LEDG, !digitalRead(LEDG));
  // }
  delay(50);
  sim800l->setPowerMode(MINIMUM);      // set minimum functionnality mode
  digitalWrite(SIM800_DTR_PIN, HIGH);  // put in sleep mode
}

void nfc_setup(void) {
  Serial.println("NFC_setup");
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }

  // Got ok data, print it out!
  Serial.print("Found chip PN5");
  Serial.println((versiondata >> 24) & 0xFF, HEX);
  Serial.print("Firmware ver. ");
  Serial.print((versiondata >> 16) & 0xFF, DEC);
  Serial.print('.');
  Serial.println((versiondata >> 8) & 0xFF, DEC);

  // configure board to read RFID tags and NFC tags
  nfc.SAMConfig();

  Serial.println("Waiting for an NFC card...");
}

//------------- ADDITIONAL FUNCTIONS ------------------------------

float getBatteryVoltage() {
  float adcCount = analogRead(PIN_VBAT);
  float adcVoltage = (adcCount / 1023.0) * 5.0;  // Convert ADC count to voltage
  return adcVoltage;
}

float getBatteryLevel() {
  const float minTension = 3.7;
  const float maxTension = 4.2;
  float batteryVoltage = getBatteryVoltage();

  float batteryLevel = (batteryVoltage - minTension) / (maxTension - minTension) * 100;

  // Constrain the battery level to 0-100%
  batteryLevel = constrain(batteryLevel, 0, 100);

  return batteryLevel;
}

// provides the absolute difference in acceleration between consecutive calls, helping to monitor changes in motion over time.
float getMotionData() {
  static float previousAcceleration = 0;
  //r
  float accelX = imu.readFloatAccelX();
  float accelY = imu.readFloatAccelY();
  float accelZ = imu.readFloatAccelZ();

  float currentAcceleration = sqrt(accelX * accelX + accelY * accelY + accelZ * accelZ) * 100;
  float MotionDataerence = currentAcceleration - previousAcceleration;  // Calculate the acceleration difference
  previousAcceleration = currentAcceleration;

  return fabs(MotionDataerence);  //returns a value always positive
}

float getRotationData() {
  static float previousRotation = 0;

  // Read gyroscope values
  float gyroX = imu.readFloatGyroX();
  float gyroY = imu.readFloatGyroY();
  float gyroZ = imu.readFloatGyroZ();

  float currentRotation = sqrt(gyroX * gyroX + gyroY * gyroY + gyroZ * gyroZ);  // Calculate the current rotation based on gyroscope readings
  float RotationDataerence = currentRotation - previousRotation;                // Calculate the difference in rotation
  previousRotation = currentRotation;                                           // Update the previous rotation value

  return fabs(RotationDataerence);
}

void Time(void) {
  unsigned long millisPassed = millis();
  unsigned int seconds = (millisPassed / 1000) % 60;
  unsigned int minutes = (millisPassed / (1000 * 60)) % 60;
  unsigned int hours = (millisPassed / (1000 * 60 * 60)) % 24;
  Serial.print("Detected at : ");
  Serial.print(hours);
  Serial.print("h");
  Serial.print(minutes);
  Serial.print("mn");
  Serial.print(seconds);
  Serial.println("s");
}

void PulseBuzzer(int repetitions, unsigned long durationOn, unsigned long durationOff) {
  static int buzzerState = LOW;
  unsigned long currentMillis = millis();

  if (currentRep < repetitions) {
    if (currentMillis - previousMillis >= (buzzerState == LOW ? durationOn : durationOff)) {
      digitalWrite(buzzerPin, buzzerState = !buzzerState);
      previousMillis = currentMillis;
      if (!buzzerState) currentRep++;
    }
  } else {
    // Reset variables after performing all repetitions
    currentRep = 0;
    previousMillis = 0;
    MotionSmall = false;
    MotionBig = false;
  }
}

void GPS_ISR() {
  if (Config.isActivate != 0) {
    if (!position_acquired) {
      start_gps = true;
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    } else {
      // digitalWrite(GPS_WKUP_PIN, LOW);
      // GPS.sendCommand("$PMTK225,4*2F");  // send to backup mode
      send_position = true;
      position_acquired = false;
    }
  }
}

void activateGPS() {
  if (start_gps == true) {
    digitalWrite(GPS_WKUP_PIN, HIGH);
    start_gps = false;
  }
}

void TimerHandler() {
  ISR_Timer.run();
}

void SIM_ISR() {
  send_position = true;
}

void onConnect(BLEDevice central) {
  Serial.print("Connected to ");
  Serial.println(central.address());
  Serial.println(BLE.address());
  digitalWrite(LEDB, LOW);
}

void onDisconnect(BLEDevice central) {
  Serial.print(F("Disconnected from central: "));
  Serial.println(central.address());
  isAuthenticate = false;
  digitalWrite(LEDB, HIGH);
}

void onWritePassword(BLEDevice central, BLECharacteristic characteristic) {
  const int motDePasseAttendu = 1;
  short int value = PasswordCharacteristic.value();
  Conversion(value);
  isAuthenticate = (value == motDePasseAttendu);
  Serial.println(isAuthenticate ? "successful authentication" : "wrong password");
}

char Conversion(unsigned short int data) {
  char mdphexadecimal[5];
  sprintf(mdphexadecimal, "%04X", data);

  for (int i = 0; i < 2; ++i) {
    char temp = mdphexadecimal[i];
    mdphexadecimal[i] = mdphexadecimal[2 + i];
    mdphexadecimal[2 + i] = temp;
  }
  //Serial.println("Mot de passe : " + String(valeur) + " ");  //used to see the value in decimal
  Serial.print("Written password  = ");
  Serial.println(mdphexadecimal);
}

void onWriteName(BLEDevice central, BLECharacteristic characteristic) {
  if (isAuthenticate) {
    Config.Name = NameCharacteristic.value();
    String value = NameCharacteristic.value();
    Serial.print("Written name : ");
    Serial.println(value);
  } else {
    NameCharacteristic.writeValue("\n");
  }
}

void onReadName(BLEDevice central, BLECharacteristic characteristic) {
  Serial.println("CALLBACK READ");
  Serial.println(isAuthenticate);
  if (isAuthenticate) {
    NameCharacteristic.writeValue(Config.Name);
  } else {
    NameCharacteristic.writeValue("\n");
  }
}

void onWriteActivation(BLEDevice central, BLECharacteristic characteristic) {
  if (isAuthenticate) {
    Config.isActivate = ActivationCharacteristic.value();
    if (Config.isActivate != 0) {
      Serial.println("Alarme enabled");
      digitalWrite(SIM800_DTR_PIN, LOW);  // put in normal mode
      delay(100);
      sim800l->setPowerMode(NORMAL);  // set normal functionnality mode
    } else {
      Serial.print("Desactivation");
      sim800l->setPowerMode(MINIMUM);      // set minimum functionnality mode
      digitalWrite(SIM800_DTR_PIN, HIGH);  // put in sleep mode
    }
  } else {
    ActivationCharacteristic.writeValue(Config.isActivate);
  }
}

void onReadActivation(BLEDevice central, BLECharacteristic characteristic) {
  // Serial.println("CALLBACK READ");
  // Serial.println(isAuthenticate);
  ActivationCharacteristic.writeValue(Config.isActivate);
}

void onWriteUnlock(BLEDevice central, BLECharacteristic characteristic) {
  if (isAuthenticate) {
    if (Config.isActivate != 0) {
      // activate electromagnet
      Serial.println("Unlock and Desactivate");
      digitalWrite(aimantPin, HIGH);
      delay(2000);
      digitalWrite(aimantPin, LOW);
      //Desactivate
      Config.isActivate = 0;
    } else {
      // activate electromagnet
      Serial.println("Unlock");
      digitalWrite(aimantPin, HIGH);
      delay(2000);
      digitalWrite(aimantPin, LOW);
    }
  }
}

String convertDMMtoDD(String dmmCoordinates) {
  int degrees;
  float minutes;
  // Separate coordinates in degrees and decimal minutes
  if (dmmCoordinates.length() == 9) {
    degrees = dmmCoordinates.substring(0, 2).toInt();
    minutes = dmmCoordinates.substring(2).toFloat();
  } else {
    degrees = dmmCoordinates.substring(0, 1).toInt();
    minutes = dmmCoordinates.substring(1).toFloat();
  }
  // Convert decimal minutes to decimal degrees
  float decimalDegrees = degrees + (minutes / 60.0);

  // Convert to string and format coordinates to decimal degrees
  String ddCoordinates = String(decimalDegrees, 10);  // You can adjust the number of decimals here

  return ddCoordinates;
}

void interruptBuzzer() {
  digitalWrite(buzzerPin, LOW);
  MotionBig = false;
  MotionSmall = false;
  MotionDetect = false;
}


// Command useful :
// activate_mode : Allows you to activate the security system
// unlock_mode : Unlock the security system
// check_battery : Show in the console the battery level
// check_voltage : Show in the console the voltage used