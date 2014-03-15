//function to write each sensor reading to the file in the SD card
//float returned from the Sensor_read() function and saved in a variable in main
void SD_write(float p, float t, File& sensorData)
{ 
  //get size of file before writing
  unsigned long size_before = sensorData.size(); 

  //write the pressure reading into the .csv file
  //saving units causes difficulty when uploading to Excel
  sensorData.print(p);
  sensorData.print(",");
  sensorData.print(t);
  sensorData.println(","); //separate with comma and move to new line
  sensorData.flush();      //save data to SD
  
  //check that data is being saved and size of file increases
  unsigned long size_after = sensorData.size();
  if (size_after > size_before)
    Serial.println("Data saved");
    
  else
    Serial.println("Data save error");
}
