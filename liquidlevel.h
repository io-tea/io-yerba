#pragma once

#include "mbed.h"
#include "io-tea/sensor/sensor.h"


namespace iotea {
    namespace yerba {

      class LiquidLevelSensor : public iotea::sensor::Sensor {
      public:
        LiquidLevelSensor(AnalogIn pin);
        virtual std::list<protocol::Message> getMessages() override;

      private:
          AnalogIn pin_;
          float read_() noexcept;
      };
  }
}
