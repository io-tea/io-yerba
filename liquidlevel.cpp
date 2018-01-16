#include "liquidlevel.h"

using namespace iotea::yerba;

LiquidLevelSensor::LiquidLevelSensor(AnalogIn pin) noexcept : pin_(pin) {}

float LiquidLevelSensor::read() noexcept {
  return pin_.read();
}
