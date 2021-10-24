#include "main.h"
#include "readtemp.h"
#include "i2cbus.h"

float ReadTemp(int Address){

float Temp;
int Temp_int,Temp_frac;
  Address *=2;

  I2C_Stop();
  I2C_Start();
  if (debug==2) printf("bus started\r\n");

  I2C_Tx_byte( 0x90 + Address );
  I2C_Tx_byte( 0xAC);
  I2C_Tx_byte( 0x2 );
  if (debug==2) printf("sensor setup\r\n");

  I2C_Start();
  I2C_Tx_byte( 0x90 + Address );
  I2C_Tx_byte( 0xEE );
  if (debug==2) printf("star convert\r\n");

  I2C_Stop();


  I2C_Start();
  I2C_Tx_byte( 0x90 + Address );
  I2C_Tx_byte( 0xAA);
  if (debug==2) printf("sensor read temp\r\n");

  I2C_Start();

  I2C_Tx_byte( 0x91 + Address );

    Temp_int  = I2C_Rx_byte(1);
    Temp_frac = I2C_Rx_byte(0);

    if (debug==2)  printf("int:%i frac:%i \r\n",Temp_int,Temp_frac);

    Temp = Temp_int+ ((float)Temp_frac/256);

    if (Temp_int >= 128)
        Temp -= 256;

    I2C_Stop();

return Temp;
}//ReadTemp

