/*  The circuit:
 * BMP085 SDA pin to analogue pin 4
 * BMP085 SCL pin to analogue pin 5
 * BMP085 EOC pin floating         
 */

void Sensor_setup(BMP085& sensor)
{    
    //calibration function from .c library source code
    //extracts all variables from EEPROM memory once
    sensor.BMP085Calib(); 
}

