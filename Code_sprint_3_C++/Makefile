CXX = g++
CXXFLAGS = -c -Wall
LDFLAGS = -lwiringPi
MUSFLAGS = -lmpg123 -lao

all:main

main: main.o kbhit.o manuel.o move_car.o spi.o music.o gps.o minmea.o scenario.o
	$(CXX) -o main main.o kbhit.o manuel.o move_car.o spi.o music.o gps.o minmea.o scenario.o $(LDFLAGS) $(MUSFLAGS)

main.o: main.cpp kbhit.h manuel.h move_car.h spi.h music.h
	$(CXX) -o main.o main.cpp $(CXXFLAGS) $(MUSFLAGS)

kbhit.o: kbhit.c kbhit.h
	 $(CXX) -o kbhit.o kbhit.c $(CXXFLAGS)

manuel.o: manuel.cpp manuel.h kbhit.h move_car.h music.h gps.h minmea.h scenario.h
	 $(CXX) -o manuel.o manuel.cpp $(CXXFLAGS) $(MUSFLAGS)

move_car.o: move_car.cpp move_car.h spi.h
	 $(CXX) -o move_car.o move_car.cpp $(CXXFLAGS)

spi.o: spi.cpp spi.h
	 $(CXX) -o spi.o spi.cpp $(CXXFLAGS)

music.o: music.cpp music.h kbhit.h
	 $(CXX) -o music.o music.cpp $(CXXFLAGS) $(MUSFLAGS)

gps.o: gps.cpp gps.h
	 $(CXX) -o gps.o gps.cpp $(CXXFLAGS)

minmea.o: minmea.c minmea.h
	 $(CXX) -o minmea.o minmea.c $(CXXFLAGS)

scenario.o: scenario.cpp gps.h spi.h scenario.h
	 $(CXX) -o scenario.o scenario.cpp $(CXXFLAGS)

clean:
	rm -rf *.o ; rm -rf main
