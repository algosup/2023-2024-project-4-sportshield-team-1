
#ifndef __PN532_SPI_H__
#define __PN532_SPI_H__

#include <SPI.h>
#include "PN532/PN532/PN532Interface.h"

class PN532_SPI : public PN532Interface {
  public:
  #if defined(ARDUINO_ARCH_RP2040)
    PN532_SPI(SPIClassRP2040& spi, uint8_t ss);
  #else
    PN532_SPI(SPIClass& spi, uint8_t ss);
  #endif

    void begin();
    void wakeup();
    int8_t writeCommand(const uint8_t* header, uint8_t hlen, const uint8_t* body = 0, uint8_t blen = 0);

    int16_t readResponse(uint8_t buf[], uint8_t len, uint16_t timeout);

  private:
  #if defined(ARDUINO_ARCH_RP2040)
    SPIClassRP2040* _spi;
  #else
    SPIClass* _spi;
  #endif
    uint8_t _ss;
    uint8_t command;

    bool isReady();
    void writeFrame(const uint8_t* header, uint8_t hlen, const uint8_t* body = 0, uint8_t blen = 0);
    int8_t readAckFrame();

    inline void write(uint8_t data) {
        _spi->transfer(data);
    };

    inline uint8_t read() {
        return _spi->transfer(0);
    };
};

#endif
