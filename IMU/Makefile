PROG = ImuCommunication
CC = g++

CPPFLAGS = -g -I /usr/local/include -std=c++11
LDFLAGS = -L /usr/local/lib  -lwiringPi -lwiringPiDev -lstdc++
OBJS = Imu.o caller.o

$(PROG) : $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $(OBJS)

caller.o : Imu.h caller.cpp
	$(CC) $(CPPFLAGS) -c caller.cpp

Imu.o : Imu.cpp Imu.hpp
	$(CC) $(CPPFLAGS) -c Imu.cpp

clean :
	rm -f core $(PROG) $(OBJS)
