//test if microSD has been inserted and upload the data from
//sensor into .csv file with timestamp on the SD
//using the predefined functions
#include <SD.h>
#include <Wire.h>
#include <Time.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

//instance of the sensor
Adafruit_BMP085_Unified sensor = Adafruit_BMP085_Unified(10085);
time_t t;
//initialised variable to save pressure value
double pressure = 0;

File sensorData;

void setup()
{
  SD_setup(sensorData);



  /* Initialise the sensor */
  if(!sensor.begin())
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

}
void loop() 
{
  
  setTime(t);
  timeStatus();
  //instance of an event 
  sensors_event_t event;
  sensor.getEvent(&event);
  
    if (event.pressure)
  {
    /* Display atmospheric pressue in hPa */
    Serial.print("Pressure:    ");
    Serial.print(event.pressure);
    Serial.println(" hPa");
    pressure = event.pressure;
  }

  else
  {
    Serial.println("Sensor error");
  }
  
  SD_write(pressure, sensorData);
  
  //10 seconds delay between readings
  delay(5000);
  
  
  

}

