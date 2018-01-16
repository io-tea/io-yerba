#pragma once

#include "mbed.h"


namespace iotea {
    namespace yerba {

      class LiquidLevelSensor {
      public:
        LiquidLevelSensor(AnalogIn pin);
        float read() noexcept;

      private:
          AnalogIn pin_;
      };
  }
}
