CXX = g++
WALLFLAG = -Wall
CFLAG = -c

WPFLAG = -lwiringPi
THFLAG = -std=c++11 -lpthread

CPPFLAGS = -g -I /usr/local/include -I/usr/include/python2.7 -std=c++11
LIBS = -lpython2.7
LDFLAGS = -L/usr/local/lib  -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect -L/usr/lib/python2.7/config/ -L/Library/Frameworks/Python.framework/Versions/3.3/lib/

MUSICFLAGS = -lmpg123 -lao

all: Geocar.o Mediator.o Model.o Navigation.o Controler.o GpsHandler.o minmea.o Spi.o Location.o LocationInterface.o router.o parserV1.o kbhit.o music.o IMU_Handler.o
	$(CXX) -o geocar_exec Geocar.o Mediator.o Model.o Navigation.o Controler.o GpsHandler.o minmea.o Spi.o Location.o LocationInterface.o router.o parserV1.o kbhit.o IMU_Handler.o music.o $(WPFLAG) $(THFLAG) $(LIBS) $(LDFLAGS) $(CPPFLAGS) $(MUSICFLAGS)

Geocar.o: Geocar.cpp Geocar.h Mediator.h Controler.h Spi.h GpsHandler.h Navigation.h kbhit.h music.h parserV1.hpp IMU_Handler.h
	$(CXX) $(CFLAG) $(WALLFLAG) Geocar.cpp -o Geocar.o $(WPFLAG) $(THFLAG) $(LIBS) $(LDFLAGS) $(CPPFLAGS) $(MUSICFLAGS)

Mediator.o: Mediator.cpp Model.h Mediator.h
	$(CXX) $(CFLAG) $(WALLFLAG) Mediator.cpp -o Mediator.o $(THFLAGS) $(CPPFLAGS)
Model.o: Model.cpp Model.h
	$(CXX) $(CFLAG) $(WALLFLAG) Model.cpp -o Model.o
Navigation.o: Navigation.cpp Navigation.h
	$(CXX) $(CFLAG) $(WALLFLAG) Navigation.cpp -o Navigation.o $(CPPFLAGS)
Controler.o: Controler.cpp Mediator.h Controler.h
	$(CXX) $(CFLAG) $(WALLFLAG) Controler.cpp -o Controler.o $(THFLAG)

GpsHandler.o: GpsHandler.cpp Mediator.h minmea.h GpsHandler.h
	$(CXX) $(CFLAG) $(WALLFLAG) GpsHandler.cpp -o GpsHandler.o $(WPFLAG) $(THFLAG)
minmea.o: minmea.c minmea.h
	$(CXX) $(CFLAG) minmea.c -o minmea.o
Spi.o: Spi.cpp Model.h const.hpp Mediator.h Spi.h
	$(CXX) $(CFLAG) $(WALLFLAG) Spi.cpp -o Spi.o $(THFLAG) $(WPFLAG)

Location.o: Location.cpp Location.h
	$(CXX) $(CFLAG) $(WALLFLAG) Location.cpp -o Location.o $(LIBS) $(LDFLAGS) $(CPPFLAGS)
LocationInterface.o: LocationInterface.cpp LocationInterface.h
	$(CXX) $(CFLAG) $(WALLFLAG) LocationInterface.cpp -o LocationInterface.o $(LIBS) $(LDFLAGS) $(CPPFLAGS)
router.o: router.cpp router.hpp
	$(CXX) $(CFLAG) $(WALLFLAG) router.cpp -o router.o $(LIBS) $(LDFLAGS) $(CPPFLAGS)
parserV1.o : parserV1.cpp rapidxml_utils.hpp router.hpp parserV1.hpp
	$(CXX) $(CFLAG) $(WALLFLAG) parserV1.cpp -o parserV1.o $(LIBS) $(LDFLAGS) $(CPPFLAGS)

kbhit.o: kbhit.cpp kbhit.h
	$(CXX) $(CFLAG) $(WALLFLAG) kbhit.cpp -o kbhit.o

IMU_Handler.o: IMU_Handler.cpp IMU_Handler.h Mediator.h
	$(CXX) $(CFLAG) $(WALLFLAG) IMU_Handler.cpp -o IMU_Handler.o $(WPFLAG) $(THFLAGS) $(CPPFLAGS)
music.o: music.cpp music.h Mediator.h
	$(CXX) $(CFLAG) $(WALLFLAG) music.cpp -o music.o $(THFLAGS) $(CPPFLAGS) $(MUSICFLAGS)
#SensorFusion.o: SensorFusion.cpp
#	$(CXX) $(CFLAG) $(WALLFLAG) SensorFusion.cpp -o SensorFusion.o
#ImuHandler.o: ImuHandler.cpp ImuHandler.h
#	$(CXX) $(CFLAG) $(WALLFLAG) ImuHandler.cpp -o ImuHandler.o $(WPFLAG) $(THFLAG)

clean:
	rm -rf *.o

mrpropre: clean
	rm -rf geocar_exec
