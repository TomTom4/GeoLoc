CXX = g++
WALLFLAG = -Wall
CFLAG = -c
LDFLAGS = -lwiringPi
THFLAGS = -lpthread

all: Geocar.o Controler.o GpsHandler.o Location.o LocationInterface.o Mediator.o Model.o Navigation.o Spi.o
	$(CXX) Geocar.o Controler.o GpsHandler.o Location.o LocationInterface.o Mediator.o Model.o Navigation.o Spi.o -o geocar_exec $(WALLFLAG) $(LDFLAGS)

Geocar.o: Geocar.cpp Geocar.h Controler.h GpsHandler.h Location.h LocationInterface.h Mediator.h Model.h Navigation.h Spi.h
	$(CXX) $(CFLAG) Geocar.cpp -o Geocar.o $(WALLFLAG) $(LDFLAGS)

Controler.o: Controler.cpp
	$(CXX) $(CFLAG) Controler.cpp -o Controler.o $(WALLFLAG) $(LDFLAGS)

GpsHandler.o: GpsHandler.cpp
	$(CXX) $(CFLAG) GpsHandler.cpp -o GpsHandler.o $(WALLFLAG) $(LDFLAGS)

ImuHandler.o: ImuHandler.cpp
	$(CXX) $(CFLAG) ImuHandler.cpp -o ImuHandler.o $(WALLFLAG) $(LDFLAGS)

Location.o: Location.cpp
	$(CXX) $(CFLAG) Location.cpp -o Location.o $(WALLFLAG) $(LDFLAGS)

LocationInterface.o: LocationInterface.cpp
	$(CXX) $(CFLAG) LocationInterface.cpp -o LocationInterface.o $(WALLFLAG) $(LDFLAGS)

Mediator.o: Mediator.cpp Model.h
	$(CXX) $(CFLAG) Mediator.cpp -o Mediator.o $(WALLFLAG) $(LDFLAGS) $(THFLAGS)

Model.o: Model.cpp
	$(CXX) $(CFLAG) Model.cpp -o Model.o $(WALLFLAG) $(LDFLAGS)

Navigation.o: Navigation.cpp
	$(CXX) $(CFLAG) Navigation.cpp -o Navigation.o $(WALLFLAG) $(LDFLAGS)

SensorFusion.o: SensorFusion.cpp
	$(CXX) $(CFLAG) SensorFusion.cpp -o SensorFusion.o $(WALLFLAG) $(LDFLAGS)

Spi.o: Spi.cpp Spi.h Mediator.h const.hpp
	$(CXX) $(CFLAG) Spi.cpp -o Spi.o $(WALLFLAG) $(LDFLAGS) $(THFLAGS)

clean:
	rm -rf *.o

mrpropre: clean
	rm -rf geocar_exec
