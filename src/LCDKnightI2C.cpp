#include "LCDKnightI2C.h"

// ---------------- CONSTRUCTOR ----------------

LCDKnight::LCDKnight(uint8_t addr) {

  _addr = addr;
}

// ---------------- INITIALIZE LCD ----------------

void LCDKnight::bin() {

  Wire.begin();

  delay(50);

  write4Bits(0x03 << 4);
  delay(5);

  write4Bits(0x03 << 4);
  delay(5);

  write4Bits(0x03 << 4);
  delay(5);

  write4Bits(0x02 << 4);

  sendCmd(0x28); // 4-bit, 2 line
  sendCmd(0x0C); // display ON
  sendCmd(0x06); // entry mode
  sendCmd(0x01); // clear

  delay(5);
}

// ---------------- CLEAR LCD ----------------

void LCDKnight::clr() {

  sendCmd(0x01);

  delay(2);
}

// ---------------- CURSOR POSITION ----------------

void LCDKnight::pos(uint8_t col, uint8_t row) {

  uint8_t rowAddr[] = {0x00, 0x40};

  sendCmd(0x80 | (col + rowAddr[row]));
}

// ---------------- PRINT TEXT ----------------

void LCDKnight::txt(String text) {

  for (int i = 0; i < text.length(); i++) {

    sendData(text[i]);
  }
}

// ---------------- BACKLIGHT ON ----------------

void LCDKnight::blon() {

  expanderWrite(0x08);
}

// ---------------- BACKLIGHT OFF ----------------

void LCDKnight::bloff() {

  expanderWrite(0x00);
}

// ---------------- SEND COMMAND ----------------

void LCDKnight::sendCmd(uint8_t cmd) {

  uint8_t highNibble = cmd & 0xF0;
  uint8_t lowNibble  = (cmd << 4) & 0xF0;

  write4Bits(highNibble);
  write4Bits(lowNibble);
}

// ---------------- SEND DATA ----------------

void LCDKnight::sendData(uint8_t data) {

  uint8_t highNibble = data & 0xF0;
  uint8_t lowNibble  = (data << 4) & 0xF0;

  write4Bits(highNibble | 0x01);
  write4Bits(lowNibble | 0x01);
}

// ---------------- WRITE 4 BITS ----------------

void LCDKnight::write4Bits(uint8_t value) {

  expanderWrite(value);

  pulseEnable(value);
}

// ---------------- ENABLE PULSE ----------------

void LCDKnight::pulseEnable(uint8_t data) {

  expanderWrite(data | 0x04);

  delayMicroseconds(1);

  expanderWrite(data & ~0x04);

  delayMicroseconds(50);
}

// ---------------- I2C WRITE ----------------

void LCDKnight::expanderWrite(uint8_t data) {

  Wire.beginTransmission(_addr);

  Wire.write(data | 0x08);

  Wire.endTransmission();
}
