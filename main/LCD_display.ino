void LCD_display(float p, LiquidCrystal LCD)
{
  LCD.clear();
  LCD.print("Pressure: ");
  LCD.setCursor(0,1); //print to second line
  LCD.print(p);
  LCD.print(" hPa");
}
