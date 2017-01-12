CXX = g++
WALLFLAG = -Wall
CFLAG = -c
LDFLAGS = -lwiringPi

all:main

main: main.o spi.o car.o gps.o navigation.o
	$(CXX) -o main main.o spi.o car.o gps.o navigation.o $(LDFLAGS) $(WALLFLAG)

main.o: main.cpp spi.hpp car.hpp gps.hpp navigation.hpp
	$(CXX) -o main.o main.cpp $(LDFLAGS) $(CFLAG) $(WALLFLAG)

spi.o: spi.cpp spi.hpp car.hpp const.hpp
	$(CXX) -o spi.o spi.cpp $(LDFLAGS) $(CFLAG) $(WALLFLAG)

car.o: car.cpp car.hpp const.hpp
	$(CXX) -o car.o car.cpp $(LDFLAGS) $(CFLAG) $(WALLFLAG)

gps.o: gps.cpp gps.hpp minmea.h
	 $(CXX) -o gps.o gps.cpp $(CFLAG) $(CXXFLAGS)

minmea.o: minmea.c minmea.h
	 $(CXX) -o minmea.o minmea.c $(CFLAG) $(CXXFLAGS)

navigation.o: navigation.cpp navigation.hpp
	 $(CXX) -o navigation.o navigation.cpp $(CFLAG) $(CXXFLAGS)

clean:
	rm -rf *.o ; rm -rf main
