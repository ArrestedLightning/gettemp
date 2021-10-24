#include <stdio.h>

#include "main.h"
#include "readtemp.h"
#include "i2cbus.h"

float ReadTemp(int Address) {
  float Temp;
  int Temp_int;
  int Temp_frac;
  Address *= 2;//shift left

  I2C_Stop();
  I2C_Start();
  if (debug == 2) {
    printf("bus started\n");
  }

  I2C_Tx_byte(0x90 + Address);
  I2C_Tx_byte(0xAC);
  I2C_Tx_byte(0x2);
  if (debug == 2) {
    printf("sensor setup\n");
  }

  I2C_Start();
  I2C_Tx_byte(0x90 + Address);
  I2C_Tx_byte(0xEE);
  if (debug == 2) {
    printf("start convert\n");
  }

  I2C_Stop();

  I2C_Start();
  I2C_Tx_byte(0x90 + Address);
  I2C_Tx_byte(0xAA);
  if (debug == 2) {
    printf("sensor read temp\n");
  }

  I2C_Start();

  I2C_Tx_byte(0x91 + Address);

  Temp_int = I2C_Rx_byte(1);
  Temp_frac = I2C_Rx_byte(0);

  if (debug == 2) {
    printf("int:%i frac:%i\n", Temp_int, Temp_frac);
  }

  Temp = (float)Temp_int + ((float)Temp_frac / 256.0f);

  if (Temp_int >= 128.0f) {
    Temp -= 256.0f;
  }

  I2C_Stop();

  return Temp;
}//ReadTemp

