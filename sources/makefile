#makefile for the pctherm software

CC= gcc
INCLUDE = .
#debug version
CFLAGS = -g3
#release version
#CFLAGS = -O


#define targets
all: gettemp

#target all
gettemp: i2cbus.o main.o readtemp.o
	$(CC) -o gettemp i2cbus.o main.o readtemp.o


#dependencies
main.o: main.c main.h readtemp.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c main.c

readtemp.o: readtemp.c readtemp.h i2cbus.h main.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c readtemp.c

i2cbus.o: i2cbus.c i2cbus.h main.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c i2cbus.c



#clear up all intermediate files
clean:
	rm *.o gettemp