void LCD_display(float p, float t, LiquidCrystal &LCD)
{ 
  LCD.clear();          //clear LCD
  
  LCD.setCursor(0, 0);   //print to first line
  LCD.print("Pres: ");
  LCD.print(p);
  LCD.print(" hPa");
  
  LCD.setCursor(0, 1);   //print to second line
  LCD.print("Temp: ");
  LCD.print(t); 
  LCD.print((char)223);  //ASCII for degree symbol
  LCD.print("C");
}
