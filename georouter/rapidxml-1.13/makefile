#Makefile for testOpenCV C++ application
#Created by Guillaume Granié 02/12/16

PROG = parserV1
CC = g++

CPPFLAGS = -g -I /usr/local/include -std=c++11
LDFLAGS = -L /usr/local/lib  -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect
OBJS = parserV1.o caller.o

$(PROG) : $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $(OBJS)

caller.o : parserV1.hpp caller.cpp
	$(CC) $(CPPFLAGS) -c caller.cpp

parserV1.o : parserV1.cpp parserV1.hpp
	$(CC) $(CPPFLAGS) -c parserV1.cpp

clean :
	rm -f core $(PROG) $(OBJS)
