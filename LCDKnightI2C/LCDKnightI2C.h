#ifndef LCDKNIGHTI2C_H
#define LCDKNIGHTI2C_H

#include <Arduino.h>
#include <Wire.h>

class LCDKnight {

  public:

    LCDKnight(uint8_t addr = 0x27);

    void bin();
    void clr();

    void pos(uint8_t col, uint8_t row);

    void txt(String text);

    void blon();
    void bloff();

  private:

    uint8_t _addr;

    void sendCmd(uint8_t cmd);
    void sendData(uint8_t data);

    void write4Bits(uint8_t value);
    void expanderWrite(uint8_t data);

    void pulseEnable(uint8_t data);
};

#endif