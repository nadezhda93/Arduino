//test if microSD has been inserted and upload the data from
//sensor into .csv file with timestamp on the SD
//using the predefined functions
#include <SD.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <custom_BMP085.h>

//instance of the sensor from custom BMP085 class
BMP085 sensor;

//create a variable of type
//LiquidCrystal(rs,rw,enable,d0,d1,d2,d3,d4,d5,d6,d7)
//omit lines that are not connected
LiquidCrystal LCD1(9, 8, 5, 4, 3, 2);

//initialised variable to save pressure value
float pressure = 0;
float temp = 0;
int counter;

//instance of file in which data will be saved
File sensorData;

void setup()
{
  //open serial comms to read values on screen
  Wire.begin();
  //baud speed standard 
  Serial.begin(9600);
  
  //initialise all components
  LCD_setup(LCD1);
  counter = SD_setup(sensorData, LCD1);
  Sensor_setup(sensor);
  
}

void loop() 
{
  temp     = Sensor_temp(sensor);       //returns value of temp as a float
  pressure = Sensor_read(sensor);       //returns value of pressure as a float
  
  LCD_display(pressure, temp, LCD1);    //send to LCD and print
  SD_write(pressure, temp, counter, sensorData); //write value of pressure onto file sensorData
  
  counter += 5;  //increment counter variable for next data set
  //change delay between every reading
  delay(5000); 
}



