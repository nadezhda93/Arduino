/*  The circuit:
 * SD CS   pin to dig. pin 10
 * SD MOSI pin to dig. pin 11
 * SD MISO pin to dig. pin 12
 * SD SCK  pin to dig. pin 13 
 */

//function to initialise the SD card and file to write in
int SD_setup(File& sensorData, LiquidCrystal& LCD)
{
  //set the pin used for Card Select, can be changed if another pin
  const int cs_pin = 10;
  int counter = 0;     //initialise data numbering
  
  //set pin 10 to output in case another pin is used for Card select
  pinMode(cs_pin, OUTPUT);
  
  //check if SD card exists
  LCD.setCursor(0,0); 
  if(!SD.begin()){
    Serial.println("SD card not detected");
    LCD.print("SD card not found!");
  }
  else
  {
    Serial.println("SD card detected!");
    LCD.print("SD card found!");
  }

  //open the file onto which data is written to 'write' mode
  //if it does not exist, create it once
  sensorData = SD.open("data.csv", FILE_WRITE);
  
  //check if sensorData contains anything
  LCD.setCursor(0, 1); //display on second row, first col
  
  //set up headers on the .csv file
  sensorData.print("Time elapsed (s)");  
  sensorData.print(",");
  sensorData.print("Pressure");
  sensorData.print(",");
  sensorData.print("Temperature");
  sensorData.println(","); //separate with comma
  sensorData.flush();      //save data to SD
  
  if(!sensorData)
  {
    Serial.println("File not found");
    LCD.print("File not found!");
  }
  else
  {
    Serial.println("File ready for writing");
    LCD.print("File ready!");
  }
  
return counter;
}

