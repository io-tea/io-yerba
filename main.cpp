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

    printf("pwm set to %.2f %%\n", mypwm.read() * 100);


    pc.printf("\n\r=====================================================\n\r");
    pc.printf("DS18B20 Configuration\n\r");
    sensorTemp.mode(PullUp);

    ROM_Code_t ROM_Code = ReadROM();
    pc.printf("Family code: 0x%X\n\r", ROM_Code.BYTES.familyCode);
    pc.printf("Serial Number: ");
    for (uint32_t i = 6; i != 0; --i) {
        pc.printf("%02X%s", ROM_Code.BYTES.serialNo[i-1], (i != 1)?":":"\r\n");
    }
    pc.printf("CRC: 0x%X\r\n", ROM_Code.BYTES.Crc);

    pc.printf("\n\rRunning temperature conversion...\n\r");
    while (1) {
        displayTemperature(pc);
        wait(0.5);
        float val = sensorLiquid.read();
        pc.printf("Liquid level: %f\r\n\r\n", val);
        wait(1);
    }
}
