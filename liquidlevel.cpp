#include "liquidlevel.h"

using namespace iotea::yerba;
using namespace iotea::protocol;

LiquidLevelSensor::LiquidLevelSensor(AnalogIn pin) noexcept : pin_(pin) {}

float LiquidLevelSensor::read_() noexcept {
  return pin_.read();
}

std::list<Message> LiquidLevelSensor::getMessages() {
    Message message(MessageType::LIQUID, read_());
    return std::list<Message>({message});
}
