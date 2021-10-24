//includes
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>

#include "i2cbus.h"
#include "main.h"

//defines
#define COM_PORT1 "/dev/ttyS0"
#define COM_PORT2 "/dev/ttyS1"
#define COM_PORT3 "/dev/ttyS2"
#define COM_PORT4 "/dev/ttyS3"

#define BAUDRATE B4800

//global vars
int fd;
struct termios oldtio;
struct termios newtio;

//functions
void Open_ComPort(char com) {
  int result,arg;

  if (debug) {
    printf("comport:%i \n", com);
  }
  switch (com) {
    case 4:
     if (debug) {
       printf("trying to open com 4 fd=");
     }
     fd = open(COM_PORT4, O_RDWR | O_NOCTTY);
     break;

    case 3:
      if (debug) {
        printf("trying to open com 3 fd=");
      }
      fd = open(COM_PORT3, O_RDWR | O_NOCTTY);
      break;

    case 2:
      if (debug) {
        printf("trying to open com 2 fd=");
      }
      fd = open(COM_PORT2, O_RDWR | O_NOCTTY);
      break;

    case 1:
    default:
      if (debug) {
        printf("trying to open com 1 fd=");
      }
      fd = open(COM_PORT1, O_RDWR | O_NOCTTY);
      break;

  }//switch

  if (debug) {
    printf("%i \r\n", fd);
  }

  tcgetattr(fd, &oldtio);
  bzero(&newtio, sizeof(newtio));
  newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;

  //enable both RTS and DTR pins
  arg = TIOCM_RTS;
  result = ioctl(fd, TIOCMBIS, &arg);
  arg = TIOCM_DTR;
  result = ioctl(fd, TIOCMBIS, &arg);
}//open comPort


int Close_ComPort(void) {
  return(close(fd));
}//close_ComPort

void I2C_Start(){
  SDA_Output();
  SDA_High();
  SCL_High();
  SDA_Low();
}//I2cStart


void I2C_Stop(void) {
  SDA_Output();
  SDA_Low();
  SCL_High();
  SDA_High();
}//I2cStop

int I2C_Tx_byte(long B) {
  int i;
  for (i = 0;i <= 7; i++) {
    if (B & 0x80) {
      I2C_tx_bit1();
    } else {
      I2C_tx_bit0();
    }
    B *= 2;
  }//for
  return I2C_rx_bit();
}//I2c_Tx_byte

int I2C_Rx_byte(int Ack) {
  int i;
  int RecData = 0;
  for (i = 0; i <= 7; i++) {
    RecData *= 2;
    if (I2C_rx_bit()) {
      RecData++;
    }
  }//for

  if (Ack) {
    I2C_tx_bit0();
  } else {
    I2C_tx_bit1();
  }

  return RecData;
}//I2C_Rx_byte

void I2C_tx_bit1(void) {
  SCL_Low();
  SDA_Output();
  SDA_High();
  SCL_High();
  SCL_Low();
}//I2C_tx_bit1

void I2C_tx_bit0(void) {
  SCL_Low();
  SDA_Output();
  SDA_Low();
  SCL_High();
  SCL_Low();
}//I2C_tx_bit1

int I2C_rx_bit(void) {
  int RxValue;

  SDA_Input();
  SCL_Low();
  SCL_High();
  RxValue = SDA_Value();
  SCL_Low();

  return(RxValue);
}//I2C_rx_bit

void SDA_Output(void) {
  int arg = TIOCM_DTR;
  ioctl(fd, TIOCMBIS, &arg);
}//SDA_Output

void SDA_Input(void) {
  int arg = TIOCM_DTR;
  ioctl(fd, TIOCMBIS, &arg);
}//SDA_Input

void SCL_High(void) {
  int arg = TIOCM_RTS;
  ioctl(fd, TIOCMBIS, &arg);
}//SCL_High

void SCL_Low(void) {
  int arg = TIOCM_RTS;
  ioctl(fd, TIOCMBIC, &arg);
}//SCL_Low

void SDA_High(void) {
  int arg = TIOCM_DTR;
  ioctl(fd, TIOCMBIS, &arg);
}//SDA_High

void SDA_Low(void) {
  int arg = TIOCM_DTR;
  ioctl(fd, TIOCMBIC, &arg);
}//SDA_Low


int SDA_Value(void) {
  int s;
  ioctl(fd, TIOCMGET, &s);

  if (s & TIOCM_CTS) {
    return 1;
  } else {
    return 0;
  }
}//SDA_Value


void Wait(void) {

//if waiting code is needed it can be put in here

}//wait

