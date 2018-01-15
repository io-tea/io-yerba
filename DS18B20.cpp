#include "DS18B20.h"
#include "DS1Wire.h"

using namespace iotea::protocol;
using namespace iotea::yerba;

TemperatureSensor::TemperatureSensor(DigitalInOut pin) : pin_(pin) {}

void TemperatureSensor::configure() {
  pin_.mode(PullUp);
};

uint32_t TemperatureSensor::read_() {
    uint32_t result = 0;

    ScratchPad_t scratchpad;
    WriteByte(pin_, SKIP_ROM);    // Skip ROM
    WriteByte(pin_, READ_SCRATCHPAD);    // Read Scrachpad
    scratchpad.LSB = ReadByte(pin_);
    scratchpad.MSB = ReadByte(pin_);
    Reset(pin_);    // terminate read as we only want temperature
    result = ((scratchpad.MSB << 8) | scratchpad.LSB);

    return result;
}

void TemperatureSensor::doConversion_() {
    WriteByte(pin_, SKIP_ROM);            // Skip ROM
    WriteByte(pin_, CONVERT);             // Convert
    while (ReadBit(pin_) == 0) {}
}

ROM_Code_t TemperatureSensor::getRom_() {
    ROM_Code_t ROM_Code;
    WriteByte(pin_, READ_ROM);    // Read ROM
    for (uint32_t i = 0; i < 8; ++i) {
        ROM_Code.rom[i] = ReadByte(pin_);
    }
    return ROM_Code;
}

// temperature is store as 7.4 fixed point format (assuming 12 bit conversion)
uint32_t TemperatureSensor::getTemperature_() {
    doConversion_();
    uint32_t temp = read_();
    float f = (temp & 0x0F) * 0.0625;    // calculate .4 part
    f += (temp >> 4);    // add 7.0 part to it
    return round(f);
}

std::list<Message> TemperatureSensor::getMessages() {
  Message message(MessageType::TEMPERATURE, getTemperature_());
  return std::list<Message>({message});
}
