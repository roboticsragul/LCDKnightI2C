#include <LCDKnightI2C.h>

LCDKnight lcd;

void setup() {

  lcd.bin();

  lcd.blon();

  lcd.pos(0,0);
  lcd.txt("KnightBot");

  lcd.pos(0,1);
  lcd.txt("Library Ready");
}

void loop() {

}