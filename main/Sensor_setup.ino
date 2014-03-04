void Sensor_setup(void)
{
  if(!sensor.begin())
  {
    Serial.print("No sensor");
    while(1);
  }
}

