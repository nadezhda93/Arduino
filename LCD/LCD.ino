
#include <LiquidCrystal.h>

//class name(pins)
LiquidCrystal lcd (12, 11, 5, 4, 3, 2);

void setup()
{
  //set up number of columns and rows
  lcd.begin(16,2);
  //print a message
  lcd.print("Hello, world!");
}

void loop()
{
  //set cursor to position (column, row)
  lcd.setCursor(0,1); //column0, row2
  //print number of seconds since reset
  lcd.print(millis()/1000);  
}
