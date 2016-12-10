CXX = g++
CXXFLAGS = -c -Wall
LDFLAGS = -lwiringPi
MUSFLAGS = -lmpg123 -lao

all:main

main: main.o kbhit.o manuel.o move_car.o spi.o music.o
	$(CXX) -o main main.o kbhit.o manuel.o move_car.o spi.o music.o $(LDFLAGS) $(MUSFLAGS)

main.o: main.cpp kbhit.h manuel.h move_car.h spi.h music.h
	$(CXX) -o main.o main.cpp $(CXXFLAGS)

kbhit.o: kbhit.cpp kbhit.h
	 $(CXX) -o kbhit.o kbhit.cpp $(CXXFLAGS)

manuel.o: manuel.cpp manuel.h kbhit.h move_car.h music.h
	 $(CXX) -o manuel.o manuel.cpp $(CXXFLAGS)

move_car.o: move_car.cpp move_car.h spi.h
	 $(CXX) -o move_car.o move_car.cpp $(CXXFLAGS)

spi.o: spi.cpp spi.h
	 $(CXX) -o spi.o spi.cpp $(CXXFLAGS)

music.o: music.cpp music.h kbhit.h
	 $(CXX) -o music.o music.cpp $(CXXFLAGS) $(MUSFLAGS)

clean:
	rm -rf *.o ; rm -rf main
