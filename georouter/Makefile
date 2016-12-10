CC = g++
CFLAGS= -Wall -I/usr/include/python2.7
LIBS = -lpython2.7
LDFLAGS = -L/usr/lib/python2.7/config-x86_64-linux-gnu/
OBJS = router.o

router: router.cpp
	$(CC) $(CFLAGS) router.cpp -o router $(LIBS)
