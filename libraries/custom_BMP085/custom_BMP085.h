#ifndef BMP085_H
#define BMP085_H

#define ADDRESS 0x77	//I2C address of the sensor

//allows use of types and const in Arduino lang.
#include "Arduino.h" 
#include <Wire.h>

class BMP085
{
public:
	BMP085();				//constructor
	void BMP085Calib();		//extract EEPROM variables
	float BMP085CalcTemp();	//calc. temp in 0.1 deg C
	float BMP085CalcPres();	//calc. pressure in Pa

private:
	static const int OSS = 0; 		//oversampling setting

	char BMP085Read8bit(unsigned char);		//read 8bit register
	int BMP085Read16bit(unsigned char);		//read 16bit register

	void BMP085_UT();	//uncompensated temp
	void BMP085_UP();	//uncompensated pressure

	//EEPROM variables as per datasheet
	//16bits each
	int _AC1, _AC2, _AC3;
	unsigned int _AC4, _AC5, _AC6;
	int _B1, _B2, _MB, _MC, _MD;
	//uncompensated t and p and b5 from datasheet
	unsigned int _UT;
	unsigned long _UP;
	long _B5;
};

#endif