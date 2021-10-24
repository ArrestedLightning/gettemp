//includes////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "readtemp.h"
#include "main.h"

//defines

//global option switches
char debug=0; //print debug output
char quietmode=0;

//global vars
char* version="gettemp version 0.01 alpha 1";

//functions
void ShowUsage();
void PollOnce(char port,char sensor);
void AllSensors(char port);
void LoopMode(char port);

int main(int argc, char *argv[] )
{
  char command;
  float temp;
  int i;

  //the vars for the options
  char showusage=0;
  char pollonce=0;
  char sensornr=0;
  char comport=0;
  char allsensors=0;
  char loopmode=0;

  if (argc==1) //no arguments print standard text
  {
    printf ("\n");
    printf ("Gettemp reads the temperature of a ds1621 sensor connected to a serial port \n");
    printf ("%s\n",version);
    printf ("\n");
    printf ("Copyright (c) 2003 Remko Levels \n");
    printf ("\n");
    printf ("Gettemp comes with ABSOLUTLY NO WARRANTY. This is free software please feel\n");
    printf ("free to distrubute it under te GPL conditions (for more info see www.gnu.org)\n");
    printf ("\n");
    printf ("For a listing of possible switches type gettemp -?\n");
    printf ("\n");
  }//if
  else
  {
    for (i=1; i<argc; i++)
      {
        if (argv[i][0] == '-') //skip argument if it don't start with a '-'
          {
            if (debug)printf("decoding arguments %c cnt: %i\n",argv[i][1],i);
            switch ( argv[i][1] )
              {

              case '?':
                showusage=1; //show the ussage of the tool
              break;

              case 'a':
                allsensors=1;
              break;

              case 'q':
                quietmode=1;
              break;

              case 'c':
                comport=argv[i][2] - '0';
              break;

              case 'd':
                debug=argv[i][2] - '0';
              break;

              case 'p':
                pollonce=1; //poll once
                sensornr = argv[i][2] - '0';
              break;

              case 'l':
                loopmode=1; //poll once
              break;

              }//switch
          }//if '-'
      }//for
  }//else

  if (debug) printf("help:%i poll:%i nr:%i com:%i\n",showusage,pollonce,sensornr,comport);

  if (showusage) ShowUsage();
  if (pollonce)  PollOnce(comport,sensornr);
  if (allsensors) AllSensors(comport);
  if (loopmode) LoopMode(comport);

  return 1;
}//main



void LoopMode(char port)
{
  char c=0;

  printf("press a key to poll all sensors 'q' to exit");
  c= getchar();

  while (c!='q')
    {
      AllSensors(port);
      c= getchar();
    }//while
}//loopmode



void AllSensors(char port)
{
  int i;
  for (i=0;i<8;i++)
    {
      PollOnce(port,i);
    }//for
}//allsensors



void PollOnce(char port,char sensor)
{
  char retries;
  float temp=0;

  Open_ComPort(port);

  retries=0;
  while ( ((int)temp==0)&&(retries<25) )
  {
    temp = ReadTemp(sensor);
    usleep(100);
    retries++;
  }//while

  if (retries>=25)
  {
    printf("sensor %i not communicating\n",sensor);
  }//if
  else
  {
    if (quietmode==0) printf("measured sensor %i temp %f\n",sensor,temp);
    if (quietmode==1) printf("%f\n",temp);
  }//else

  Close_ComPort();
}//pollonce



void ShowUsage()
{
  printf ("\n");
  printf ("Gettemp reads the temperature of a ds1621 sensor connected to a serial port \n");
  printf ("%s\n",version);
  printf ("\n");
  printf ("Copyright (c) 2003 Remko Levels \n");
  printf ("\n");
  printf ("usage:\n");
  printf ("  gettemp [<options>]\n");
  printf ("Where <options> is one of more of:\n");
  printf ("\n");
  printf ("-?:		Prints this helptext\n");
  printf ("-px:		Poll a sensor once where x is the sensor adres (0 is the first sensor)\n");
  printf ("-cx:		Set the commport the sensor is connected to (x is the number of the commport)\n");
  printf ("-dx:		Print debug output with the debug level 1..2\n");
  printf ("-q:		Quiet mode only output measured temp\n");
  printf ("-a:		Poll all sensors adresses 0..7\n");
  printf ("-l:          Poll all the sensors continiues\n");
  printf ("\n");
  printf ("\n");
}//showusage


//eof
