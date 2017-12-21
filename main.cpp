#include "mbed.h"
#include <stdint.h>
#include "DS18B20.h"

DigitalInOut sensorTemp(D3);     // sensor connected to pin 5
AnalogIn sensorLiquid(A0);

PwmOut mypwm(PWM_OUT);

Ticker timer;                // used for our microsec timing
Serial pc(USBTX, USBRX);     // serial comms over usb back to console

int main() {
    pc.baud(115200);


    mypwm.period_ms(10);
    mypwm.pulsewidth_ms(1);

    sensorTemp.mode(PullUp);

    pc.printf("\n\rRunning temperature conversion...\n\r");
    while (1) {
        uint32_t temperature = getTemperature();
        pc.printf("Temperature: %d\r\n\r\n", temperature);
        wait(0.5);
        float val = sensorLiquid.read();
        pc.printf("Liquid level: %f\r\n\r\n", val);
        wait(1);
    }
}
