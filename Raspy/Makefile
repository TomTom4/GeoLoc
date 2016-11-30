CXX = g++
CXXFLAGS = -c -Wall
LDFLAGS = -lwiringPi 
MUSFLAGS = -lmpg123 -lao

all:main

main: main.o kbhit.o manuel.o move_car.o spi.o music.o
	$(CXX) -o main main.o kbhit.o manuel.o move_car.o spi.o music.o $(LDFLAGS) $(MUSFLAGS)

main.o: main.c kbhit.h manuel.h move_car.h spi.h music.h
	$(CXX) -o main.o main.c $(CXXFLAGS)

kbhit.o: kbhit.c kbhit.h
	 $(CXX) -o kbhit.o kbhit.c $(CXXFLAGS)

manuel.o: manuel.c manuel.h kbhit.h move_car.h music.h
	 $(CXX) -o manuel.o manuel.c $(CXXFLAGS)

move_car.o: move_car.c move_car.h spi.h
	 $(CXX) -o move_car.o move_car.c $(CXXFLAGS)

spi.o: spi.c spi.h
	 $(CXX) -o spi.o spi.c $(CXXFLAGS)

music.o: music.c music.h kbhit.h
	 $(CXX) -o music.o music.c $(CXXFLAGS) $(MUSFLAGS)

clean:
	rm -rf *.o ; rm -rf main

