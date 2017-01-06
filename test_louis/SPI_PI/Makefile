CXX = g++
WALLFLAG = -Wall
CFLAG = -c
LDFLAGS = -lwiringPi

all:main

main: main.o spi.o car.o
	$(CXX) -o main main.o spi.o car.o $(LDFLAGS) $(WALLFLAG)

main.o: main.cpp spi.hpp car.hpp
	$(CXX) -o main.o main.cpp $(LDFLAGS) $(CFLAG) $(WALLFLAG)

spi.o: spi.cpp spi.hpp car.hpp const.hpp
	$(CXX) -o spi.o spi.cpp $(LDFLAGS) $(CFLAG) $(WALLFLAG)

car.o: car.cpp car.hpp const.hpp
	$(CXX) -o car.o car.cpp $(LDFLAGS) $(CFLAG) $(WALLFLAG)

clean:
	rm -rf *.o ; rm -rf main
