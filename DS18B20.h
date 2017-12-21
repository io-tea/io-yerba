#ifndef _DS18B20_
#define _DS18B20_

#include <stdint.h>
#include "mbed.h"

// Device Faimly ID and Setial number information
typedef union {
    uint8_t rom[8];
    struct {
        uint8_t    familyCode;
        uint8_t    serialNo[6];
        uint8_t    Crc;
    } BYTES;
} ROM_Code_t;

ROM_Code_t ReadROM();

uint32_t getTemperature() ;

#endif
