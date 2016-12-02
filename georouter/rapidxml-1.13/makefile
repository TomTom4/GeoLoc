#Makefile for testOpenCV C++ application
#Created by Guillaume Granié 02/12/16

PROG = testOpenCV-last
CC = g++

CPPFLAGS = -g -I /usr/local/include
LDFLAGS = -L /usr/local/lib  -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect
OBJS = opencvtest.o

$(PROG) : $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $(OBJS)

test.o : test.hpp
	$(CC) $(CPPFLAGS) -c test.cpp

clean :
	rm -f core $(PROG) $(OBJS)
