/*float Sensor_read(BMP085& sensor)
{
  float pressure = 0;      //initialise pressure variable
  sensors_event_t event;   //create instance of the sensors_event_t class 
  sensor.getEvent(&event); 

  if(event.pressure)
  {
    //Display atmospheric pressue in hPa
    Serial.print("Pressure:    ");
    Serial.print(event.pressure);
    Serial.println(" hPa");
    pressure = event.pressure;
  }
  else
    Serial.print("Cannot read pressure");
    
  return pressure;
}*/

