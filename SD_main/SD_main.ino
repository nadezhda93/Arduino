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
LiquidCrystal LCD(12, 11, 5, 4, 3, 2);

//initialised variable to save pressure value
float pressure = 0;

//instance of file in which data will be saved
File sensorData;

void setup()
{
  SD_setup(sensorData);

  //Sensor_setup();
  LCD_setup(LCD);

  //-----------
  // Initialise the sensor within Sensor_setup() function
  //check if object returns 1 or zero
  if(!sensor.begin())
  {
    Serial.print("No BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1); //continue waiting infinitely
  }
  //------------

}
void loop() 
{

  //------------
  //instance of an event within Sensor_read() func
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
    Serial.println("Sensor error");
  //--------------

  //double pressure = Sensor_read(); <- returns value of pressure as a float
  LCD_display(pressure, LCD);
  SD_write(pressure, sensorData);

  //5 seconds delay between readings in main because of loop
  delay(5000);
}



