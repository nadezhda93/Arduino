#include <custom_BMP085.h>
#include <Wire.h>

BMP085 sensor;
float temp = 0;
long pressure = 0;
void setup()
{
  
  Wire.begin();
  Serial.begin(9600);
  
  sensor.BMP085Calib(); 
}

void loop()
{
  
  temp = sensor.BMP085CalcTemp();
  Serial.print("Temp: ");
  Serial.println(temp, DEC);
  
  pressure = sensor.BMP085CalcPres();
  Serial.print("Pressure (hPa): ");
  Serial.println(pressure);
  
  delay(3000);
}


