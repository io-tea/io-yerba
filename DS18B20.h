#pragma once

#include <stdint.h>

#include "mbed.h"

// Device byte commands over 1-wire serial
enum COMMANDS { READ_ROM = 0x33, CONVERT = 0x44, READ_SCRATCHPAD = 0xBE,  SKIP_ROM = 0xCC };

// device onboard register layout
typedef struct {
    uint8_t    LSB;
    uint8_t    MSB;
    uint8_t    Th;
    uint8_t    Tl;
    uint8_t    config;
    uint8_t    reserved0xFF;
    uint8_t    reserved0xCH;
    uint8_t    reserved0x10;
    uint8_t    Crc;
} ScratchPad_t;

// Device Faimly ID and Setial number information
typedef union {
    uint8_t rom[8];
    struct {
        uint8_t    familyCode;
        uint8_t    serialNo[6];
        uint8_t    Crc;
    } BYTES;
} ROM_Code_t;

namespace iotea {
    namespace yerba {

      class TemperatureSensor {
      public:
        TemperatureSensor(DigitalInOut pin) noexcept;
        virtual void configure();
        uint32_t getTemperature();

      private:
          DigitalInOut pin_;
          uint32_t read_();
          void doConversion_();
          ROM_Code_t getRom_();
      };
  }
}
