//function to write each sensor reading to the file in the SD card
//float returned from the Sensor_read() function and saved in a variable in main
void SD_write(float p, File& sensorData)
{
  //check that value is passed from main
  //Serial.println(p);
  //Serial.println("^passed");
          
  //write the pressure reading into the .csv file
  sensorData.print(p);
  //sensorData.print(" hPa"); saving units causes difficulty when uploading to Excel
  sensorData.println(",");
  sensorData.flush(); //save data to SD
  
  //check that data is being saved and size of file increases
  //Serial.println(sensorData.size());
}
