float Sensor_read(BMP085& sensor)
{
  float pressure = 0;                  //initialise pressure variable
  pressure = sensor.BMP085CalcPres();  //get pressure and save to variable
  
  //test if value has been modified
  if(pressure)
  {
    //Display atmospheric pressue in hPa
    Serial.print("Pressure:    ");
    Serial.print(pressure); //only prints long
    Serial.println(" hPa");
  }
  else
    Serial.print("Cannot read pressure");
    
  return pressure;
}

