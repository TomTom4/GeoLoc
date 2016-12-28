all: Geocar.o CapModel.o Controler.o GpsHandler.o ImuHandler.o Location.o LocationInterface.o Mediator.o Model.o Navigation.o SensorFusion.o Spi.o
	g++ Geocar.o CapModel.o Controler.o GpsHandler.o ImuHandler.o Location.o LocationInterface.o Mediator.o Model.o Navigation.o SensorFusion.o Spi.o -o geocar_exec

Geocar.o: Geocar.cpp Geocar.h CapModel.h Controler.h GpsHandler.h ImuHandler.h Location.h LocationInterface.h Mediator.h Model.h Navigation.h SensorFusion.h Spi.h
	g++ -c Geocar.cpp -o Geocar.o

CapModel.o: CapModel.cpp
	g++ -c CapModel.cpp -o CapModel.o

Controler.o: Controler.cpp
	g++ -c Controler.cpp -o Controler.o

GpsHandler.o: GpsHandler.cpp
	g++ -c GpsHandler.cpp -o GpsHandler.o

ImuHandler.o: ImuHandler.cpp
	g++ -c ImuHandler.cpp -o ImuHandler.o

Location.o: Location.cpp
	g++ -c Location.cpp -o Location.o

LocationInterface.o: LocationInterface.cpp
	g++ -c LocationInterface.cpp -o LocationInterface.o

Mediator.o: Mediator.cpp
	g++ -c Mediator.cpp -o Mediator.o

Model.o: Model.cpp
	g++ -c Model.cpp -o Model.o

Navigation.o: Navigation.cpp
	g++ -c Navigation.cpp -o Navigation.o

SensorFusion.o: SensorFusion.cpp
	g++ -c SensorFusion.cpp -o SensorFusion.o

Spi.o: Spi.cpp 
	g++ -c Spi.cpp -o Spi.o
clean:
	rm -rf *.o

mrpropre: clean
	rm -rf geocar_exec
