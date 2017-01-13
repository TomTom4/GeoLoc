CXX = g++
WALLFLAG = -Wall
CFLAG = -c
CPPFLAGS = -g -I /usr/local/include -Wall -I/usr/include/python2.7 -std=c++11

LIBS = -lpython2.7

LDFLAGS = -lwiringPi -L/usr/local/lib  -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect -L/usr/lib/python2.7/config/ -L/Library/Frameworks/Python.framework/Versions/3.3/lib/

THFLAGS = -lpthread

all: Geocar.o Controler.o GpsHandler.o Location.o LocationInterface.o Mediator.o Model.o Navigation.o Spi.o parserV1.o router.o
	$(CXX) Geocar.o Controler.o GpsHandler.o Location.o LocationInterface.o Mediator.o Model.o Navigation.o Spi.o parserV1.o router.o -o geocar_exec $(WALLFLAG) $(LDFLAGS) $(THFLAGS) $(LIBS)

Geocar.o: Geocar.cpp Geocar.h Controler.h GpsHandler.h Location.h LocationInterface.h Mediator.h Model.h Navigation.h Spi.h
	$(CXX) $(CFLAG) $(CPPFLAGS) Geocar.cpp -o Geocar.o $(WALLFLAG) $(LDFLAGS) $(THFLAGS) $(LIBS)

Controler.o: Controler.cpp
	$(CXX) $(CFLAG) $(CPPFLAGS) Controler.cpp -o Controler.o $(WALLFLAG) $(LDFLAGS) $(LIBS)

GpsHandler.o: GpsHandler.cpp
	$(CXX) $(CFLAG) $(CPPFLAGS) GpsHandler.cpp -o GpsHandler.o $(WALLFLAG) $(LDFLAGS) $(LIBS)

ImuHandler.o: ImuHandler.cpp
	$(CXX) $(CFLAG) $(CPPFLAGS) ImuHandler.cpp -o ImuHandler.o $(WALLFLAG) $(LDFLAGS) $(LIBS)

Location.o: Location.cpp
	$(CXX) $(CFLAG) $(CPPFLAGS) Location.cpp -o Location.o $(WALLFLAG) $(LDFLAGS) $(LIBS)

LocationInterface.o: LocationInterface.cpp
	$(CXX) $(CFLAG) $(CPPFLAGS) LocationInterface.cpp -o LocationInterface.o $(WALLFLAG) $(LDFLAGS) $(LIBS)

Mediator.o: Mediator.cpp Model.h
	$(CXX) $(CFLAG) $(CPPFLAGS) Mediator.cpp -o Mediator.o $(WALLFLAG) $(LDFLAGS) $(THFLAGS) $(LIBS)

Model.o: Model.cpp
	$(CXX) $(CFLAG) $(CPPFLAGS) Model.cpp -o Model.o $(WALLFLAG) $(LDFLAGS) $(LIBS)

Navigation.o: Navigation.cpp
	$(CXX) $(CFLAG) $(CPPFLAGS) Navigation.cpp -o Navigation.o $(WALLFLAG) $(LDFLAGS) $(LIBS)

SensorFusion.o: SensorFusion.cpp
	$(CXX) $(CFLAG) $(CPPFLAGS) SensorFusion.cpp -o SensorFusion.o $(WALLFLAG) $(LDFLAGS) $(LIBS)

Spi.o: Spi.cpp Spi.h Mediator.h const.hpp
	$(CXX) $(CFLAG) $(CPPFLAGS) Spi.cpp -o Spi.o $(WALLFLAG) $(LDFLAGS) $(THFLAGS) $(LIBS)

router.o: router.cpp router.hpp
	$(CC) $(CPPFLAGS) -c router.cpp $(LIBS)

parserV1.o : parserV1.cpp parserV1.hpp
	$(CC) $(CPPFLAGS) -c parserV1.cpp $(LDFLAGS) $(LIBS)


clean:
	rm -rf *.o

mrpropre: clean
	rm -rf geocar_exec
