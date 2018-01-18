#include "io-tea/node.h"
#include "mbed.h"
#include "DS18B20.h"
#include "liquidlevel.h"

iotea::yerba::TemperatureSensor temperatureSensor(D3);
iotea::yerba::LiquidLevelSensor liquidLevelSensor(A0);


int main() {
    setupSerial("YERBA - temperature and liquid sensors");
    setupNodeRadio(0xABCDEF02);
    setupTicker();

    time_t lastStatsTime = time(nullptr) - 1;
    while (true) {
        sleep();

        time_t now = time(nullptr);
        if (lastStatsTime != now) {
            lastStatsTime = now;
            printStatus();
        }

        if (tick) {
            tick = false;
            sendCoapMessage("t", std::to_string(temperatureSensor.getTemperature()));
            sendCoapMessage("l", std::to_string(liquidLevelSensor.read()));
        }
    }
}
