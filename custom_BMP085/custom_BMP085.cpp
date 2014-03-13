#include "Arduino.h"
#include "custom_BMP085.h"

//object constructor of class BMP085
BMP085::BMP085()
{
}


// Read 1 byte from the BMP085 at address
char BMP085::BMP085Read8bit(unsigned char address)
{
  unsigned char data;

  Wire.beginTransmission(ADDRESS);
  Wire.write(address);
  Wire.endTransmission();

  Wire.requestFrom(ADDRESS, 1);
  while(!Wire.available());

  return Wire.read();
}


// read 2 bytes from the sensor 16bits
// first byte from address given
// second byte from address + 1
int BMP085::BMP085Read16bit(byte address)
{
  	//most significant and least sig. bits
	unsigned char MSB, LSB;
  
	Wire.beginTransmission(ADDRESS);
  	Wire.write(address);
  	Wire.endTransmission();
  	
  	//request 2 bytes from 0x77 address
  	Wire.requestFrom(ADDRESS, 2);
  	while(Wire.available() < 2);
  	MSB = Wire.read();
  	LSB = Wire.read();
  
  	return (int) MSB << 8 | LSB; //convert to int
}


void BMP085::BMP085Calib()
{
  	_AC1 = BMP085Read16bit(0xAA);
  	_AC2 = BMP085Read16bit(0xAC);
  	_AC3 = BMP085Read16bit(0xAE);
  	_AC4 = BMP085Read16bit(0xB0);
  	_AC5 = BMP085Read16bit(0xB2);
  	_AC6 = BMP085Read16bit(0xB4);
  	_B1  = BMP085Read16bit(0xB6);
  	_B2  = BMP085Read16bit(0xB8);
  	_MB  = BMP085Read16bit(0xBA);
  	_MC  = BMP085Read16bit(0xBC);
  	_MD  = BMP085Read16bit(0xBE);

  	//print values of registers to screen
  	Serial.print("AC1 = ");
  	Serial.println(_AC1);
  	Serial.print("AC2 = ");
	Serial.println(_AC2);
  	Serial.print("AC3 = ");
	Serial.println(_AC3);
  	Serial.print("AC4 = ");
	Serial.println(_AC4);
  	Serial.print("AC5 = ");
	Serial.println(_AC5);
  	Serial.print("AC6 = ");
	Serial.println(_AC6);
  	Serial.print("B1 = ");
	Serial.println(_B1);
  	Serial.print("B2 = ");
	Serial.println(_B2);
  	Serial.print("MB = ");
	Serial.println(_MB);
  	Serial.print("MC = ");
	Serial.println(_MC);
  	Serial.print("MD = ");
	Serial.println(_MD);
}

// Read the uncompensated temperature value
void BMP085::BMP085_UT()
{ 
  	_UT = 0;
  	// write 0x2E into register 0xF4
  	// request a temperature reading
  	Wire.beginTransmission(ADDRESS);
  	Wire.write(0xF4);
  	Wire.write(0x2E);
  	Wire.endTransmission();
  
  	// wait 5ms - datasheet
  	delay(5);
  
  	// read two bytes from registers 0xF6 and 0xF7
  	_UT = BMP085Read16bit(0xF6);

  	//Serial.print("_UT = ");
  	//Serial.println(_UT);
}

// Read the uncompensated pressure value
void BMP085::BMP085_UP()
{
  	unsigned char MSB, LSB, XLSB;
  	_UP = 0;
  
  	// write 0x34+(OSS<<6) into register 0xF4
  	// request a pressure reading with oversampling setting
  	Wire.beginTransmission(ADDRESS);
  	Wire.write(0xF4);
  	Wire.write(0x34 + (OSS << 6));
  	Wire.endTransmission();
  
  	// wait for conversion,  dependent on OSS
  	delay(2 + (3 << OSS));
  
  	// read registers 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
  	Wire.beginTransmission(ADDRESS);
  	Wire.write(0xF6);
  	Wire.endTransmission();
  	Wire.requestFrom(ADDRESS, 3);
  
  	// Wait for data to become available
  	while(Wire.available() < 3);

  	MSB = Wire.read();
  	LSB = Wire.read();
  	XLSB = Wire.read();
  
  	_UP = (((unsigned long) MSB << 16) | ((unsigned long) LSB << 8) | (unsigned long) XLSB) >> (8 - OSS);
  
  	//Serial.print("_UP = ");
  	//Serial.println(_UP);
}


// Calculate temperature given UT
float BMP085::BMP085CalcTemp()
{
  	// get calue for uncom. temp
  	BMP085_UT();

  	long X1, X2;
  	float true_temp = 0;

  	//divide by 2^N same as shifting N bits to right (>>)
  	X1 = (((long)_UT - (long)_AC6)*(long)_AC5) >> 15;
  	//multiply by 2^N same as shifting N bits to left (<<)
  	X2 = ((long)_MC << 11)/(X1 + _MD);
  	_B5 = X1 + X2;

  	true_temp = (_B5 + 8) >> 4; 

  	return (true_temp*0.1);  
}



// Calculate pressure given up
// calibration values must be known
// b5 is also required so bmp085GetTemperature(...) must be called first.
// Value returned will be pressure in units of Pa.
long BMP085::BMP085CalcPres()
{
  BMP085_UP();
  long X1, X2, X3, B3, B6, pressure;
  unsigned long B4, B7;
  
  B6 = _B5 - 4000;

  // Calculate B3
  X1 = (_B2 * (B6 * B6)>>12)>>11;
  X2 = (_AC2 * B6)>>11;
  X3 = X1 + X2;
  B3 = (((((long)_AC1)*4 + X3)<<OSS) + 2)>>2;
  
  // Calculate B4
  X1 = (_AC3 * B6)>>13;
  X2 = (B1 * ((B6 * B6)>>12))>>16;
  X3 = ((X1 + X2) + 2)>>2;
  B4 = (_AC4 * (unsigned long)(X3 + 32768))>>15;
  
  B7 = ((unsigned long)(_UP - B3) * (50000>>OSS));
  if (B7 < 0x80000000)
    pressure = (B7<<1)/B4;
  else
    pressure = (B7/B4)<<1;
    
  X1 = (pressure >> 8) * (pressure >> 8);
  X1 = (X1 * 3038)>>16;
  X2 = (-7357 * pressure)>>16;
  pressure += (X1 + X2 + 3791)>>4;
  
  return (pressure/100);
}
