//includes
#include <sys/types.h>
#include <sys/stat.h>
#include <asm/ioctls.h>
#include <asm/termios.h>
#include <fcntl.h>
#include <stdio.h>


//defines
#define DEBUG 1
#define COM_PORT "/dev/ttyS0"
#define BAUDRATE B4800
//global vars

//function

int main()
{
  int fd;
  int error=0;
  struct termios oldtio,newtio;
  int arg = TIOCM_CTS;
  int arg2= TIOCM_RTS;
  int arg3= TIOCM_DTR;
  int result;
  char command;

  if (DEBUG) printf("trying to open com port filedescr=");
  fd = open(COM_PORT, O_RDWR | O_NOCTTY);
  if (DEBUG) printf("%i \r\n",fd);

  tcgetattr(fd,&oldtio);

  bzero(&newtio, sizeof(newtio));
  newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;

  command = 'a';
  while (command!='q'){
    switch (command)
    {
    case 's':
      result = ioctl(fd, TIOCMBIS, &arg);
      if (DEBUG) printf("set result cts was %i\r\n",result);
    break;

    case 'x':
      result = ioctl(fd, TIOCMBIC, &arg);
      if (DEBUG) printf("clr result cts was %i\r\n",result);
    break;

    case 'd'://werkt
      result = ioctl(fd, TIOCMBIS, &arg2);
      if (DEBUG) printf("set result rts was %i\r\n",result);
    break;

    case 'c'://werkt
      result = ioctl(fd, TIOCMBIC, &arg2);
      if (DEBUG) printf("clr result rts was %i\r\n",result);
    break;

    case 'f'://werkt
      result = ioctl(fd, TIOCMBIS, &arg3);
      if (DEBUG) printf("set result dtr was %i\r\n",result);
    break;

    case 'v'://werkt
      result = ioctl(fd, TIOCMBIC, &arg3);
      if (DEBUG) printf("clr result dtr was %i\r\n",result);
    break;

    default:
    break;
    }//switch
  command = getchar();
  }//while



  getchar();

  if (DEBUG) printf("closing com port\r\n");


  error = close(fd);

  return error;
}


//eof

