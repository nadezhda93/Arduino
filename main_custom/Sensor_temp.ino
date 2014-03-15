long Sensor_temp(BMP085& sensor) //pass in sensor object of type BMP085
{
  float temperature = 0;                  //initialise temp variable
  temperature = sensor.BMP085CalcTemp();  //get temperature and save to variable

  //test if value has been modified
  if(temperature)
  {     
    //Display atmospheric pressue in hPa
    Serial.print("Temperature:    ");
    Serial.print(temperature);
    Serial.println(" C");
  }
  else
    Serial.print("Cannot read temperature");

  return temperature;
}

