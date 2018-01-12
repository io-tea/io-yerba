#include "liquidlevel.h"

using namespace iotea::yerba;
using namespace iotea::protocol;

LiquidLevelSensor::LiquidLevelSensor(PinName pin) noexcept : analogIn(pin) {}

float LiquidLevelSensor::read_() noexcept {
  return pin_.read();
}

std::list<Message> LiquidLevelSensor::getMessages() {
    Message message(MessageType::LIQUID, read());
    return std::list<Message>({message});
}
