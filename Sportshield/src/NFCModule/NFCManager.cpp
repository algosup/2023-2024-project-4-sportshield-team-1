#include "NFCManager.h"

NFCManager::NFCManager(uint8_t sda, uint8_t scl) : nfc(sda, scl), isTagPresent(false) {
}

void NFCManager::begin() {
    nfc.begin();
    uint32_t versiondata = nfc.getFirmwareVersion();
    if (!versiondata) {
        Serial.print("Didn't find PN53x board");
        while (1); // halt
    }
    // Configure board to read RFID tags
    nfc.SAMConfig();
}

bool NFCManager::scanForTag() {
    isTagPresent = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, (uint8_t *)&tagUID, &uidLength);
    return isTagPresent;
}

String NFCManager::readTagUID() {
    if (isTagPresent) {
        String uidString = "";
        for (uint8_t i = 0; i < uidLength; i++) {
            uidString += String(tagUID[i], HEX);
        }
        return uidString.toUpperCase();
    } else {
        return String("No Tag");
    }
}
