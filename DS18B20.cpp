#include "DS18B20.h"
#include "DS1Wire.h"
#include "mbed.h"
#include <stdint.h>

void TemperatureSensor::doConversion_() {
    Reset(pin_);
    WriteByte(pin_, SKIP_ROM);            // Skip ROM
    WriteByte(pin_, CONVERT);             // Convert
    while (ReadBit(pin_) == 0) {}
}

uint32_t TemperatureSensor::getTemperature_() {
    uint32_t result = 0;

    Reset(pin_);

    ScratchPad_t scratchpad;
    WriteByte(pin_, SKIP_ROM);    // Skip ROM
    WriteByte(pin_, READ_SCRATCHPAD);    // Read Scrachpad
    scratchpad.LSB = ReadByte(pin_);
    scratchpad.MSB = ReadByte(pin_);
    Reset(pin_);    // terminate read as we only want temperature
    result = ((scratchpad.MSB << 8) | scratchpad.LSB);

    return result;
}

ROM_Code_t TemperatureSensor::getRom() {
    ROM_Code_t ROM_Code;
    Reset(pin_);
    WriteByte(pin_, READ_ROM);    // Read ROM
    for (uint32_t i = 0; i < 8; ++i) {
        ROM_Code.rom[i] = ReadByte(pin_);
    }
    return ROM_Code;
}

// temperature is store as 7.4 fixed point format (assuming 12 bit conversion)
uint32_t TemperatureSensor::getTemperature() {
    doConversion_();
    uint32_t temp = getTemperature_();
    float f = (temp & 0x0F) * 0.0625;    // calculate .4 part
    f += (temp >> 4);    // add 7.0 part to it
    return round(f);
}
