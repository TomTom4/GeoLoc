CXX = g++
CXXFLAGS = -c -Wall

all:main

main: main.o spi.o car.o
	$(CXX) -o main main.o spi.o car.o $(CXXFLAGS)

main.o: main.cpp spi.hpp car.hpp
	$(CXX) -o main.o main.cpp $(CXXFLAGS)

spi.o: spi.cpp spi.hpp car.hpp
		$(CXX) -o spi.o spi.cpp $(CXXFLAGS)

car.o: car.cpp car.hpp
	 $(CXX) -o car.o car.cpp $(CXXFLAGS)

clean:
	rm -rf *.o ; rm -rf main
