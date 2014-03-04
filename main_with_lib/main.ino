//test if microSD has been inserted and upload the data from
//sensor into .csv file with timestamp on the SD
//using the predefined functions
#include <SD.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

//instance of the sensor from Adafruit class
Adafruit_BMP085_Unified sensor = Adafruit_BMP085_Unified(10085);

//create a variable of type
//LiquidCrystal(rs,rw,enable,d0,d1,d2,d3,d4,d5,d6,d7)
//omit lines that are not connected
LiquidCrystal LCD(9, 8, 5, 4, 3, 2);

//initialised variable to save pressure value
float pressure, temp = 0;

//instance of file in which data will be saved
File sensorData;

void setup()
{
  //initialise all components
  LCD_setup(LCD);
  SD_setup(sensorData);
  Sensor_setup();
}

void loop() 
{
  pressure = Sensor_read();        //returns value of pressure as a float
  temp     = Sensor_temp(sensor);
  LCD_display(pressure, temp, LCD);      //send to LCD and print
  SD_write(pressure, sensorData);  //write value of pressure onto file sensorData

  //t ms seconds delay between readings in main because of loop
  delay(5000); 
}



