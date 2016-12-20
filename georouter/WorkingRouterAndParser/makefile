#Makefile for testOpenCV C++ application
#Created by Guillaume Granié 02/12/16

PROG = parserAndRouter
CC = g++

CPPFLAGS = -g -I /usr/local/include -Wall -I/usr/include/python2.7 -std=c++11
LIBS = -lpython2.7 
LDFLAGS = -L/usr/local/lib  -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect -L/usr/lib/python2.7/config/ -L/Library/Frameworks/Python.framework/Versions/3.3/lib/
OBJS = parserV1.o caller.o router.o

$(PROG) : $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $(OBJS) $(LIBS)

router.o: router.cpp router.hpp
	$(CC) $(CPPFLAGS) -c router.cpp $(LIBS)

caller.o : parserV1.hpp router.hpp caller.cpp
	$(CC) $(CPPFLAGS) -c caller.cpp

parserV1.o : parserV1.cpp parserV1.hpp
	$(CC) $(CPPFLAGS) -c parserV1.cpp

clean :
	rm -f core $(PROG) $(OBJS)
