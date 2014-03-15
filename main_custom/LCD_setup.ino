/*  The circuit:
 * LCD RS pin to dig. pin 9
 * LCD En pin to dig. pin 8
 * LCD D4 pin to dig. pin 5
 * LCD D5 pin to dig. pin 4
 * LCD D6 pin to dig. pin 3
 * LCD D7 pin to dig. pin 2
 * LCD R/W pin to GND
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 (optional)
 */

void LCD_setup(LiquidCrystal &LCD)
{
  //set up number of columns and rows 16x2
  LCD.begin(16, 2);
  //set cursor at start
  LCD.home();
}
