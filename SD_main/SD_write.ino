//function to write each sensor reading to the file in the SD card
//if you wish to modify object, leave out 'const'
void SD_write(float p, File& sensorData)
{
  Serial.println(p);
  Serial.println("^passed");
  
  //write the value into the .csv file
  //sensorData.print(p);
  //sensorData.print(" hPa");
  //sensorData.println(",");
  //sensorData.flush(); //save data to SD
  
  //Serial.println(sensorData.size());
}
