//function to initialise the SD card and file to write in
void SD_setup(File& sensorData)
{
  //set the pin used for Card Select, can be changed if another pin
  const int cs_pin = 10;

  //open serial communications and set speed to 9600 bps
  Serial.begin(9600);

  //set pin 10 to output in case another pin is used for Card select
  pinMode(10, OUTPUT);
  
  //use LEDs to blink and detect faults while on battery
  if(!SD.begin())
    Serial.println("SD card not detected");
  else
    Serial.println("SD card found!");

  //open the file onto which data is written to 'write' mode
  //if it does not exist, create it once
  sensorData = SD.open("data.csv", FILE_WRITE);
  
  //check if sensorData contains anything
  if(!sensorData)
    Serial.println("File not found");
  else
    Serial.println("File ready for writing");
  
}

