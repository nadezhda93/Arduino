float Sensor_temp(BMP085& sensor) //pass in sensor object of type BMP085
{
  temp = sensor.BMP085CalcTemp();
  return temp; 
}
