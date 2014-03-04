float Sensor_temp(Adafruit_BMP085_Unified sensor) //pass in sensor object of type Adafruit
{
  float temp = 0; //initialise temp variable
  
  sensor.getTemperature(&temp);
  
  return temp; 
}
