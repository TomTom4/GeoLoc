#ifndef DEF_SPI
#define DEF_SPI

#include <iostream>
#include <stdio.h>
#include <string>

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <pthread.h>
#include <assert.h>

#include "Model.h"
#include "Spi.h"
#include "const.hpp"

#include "Mediator.h"

class Spi /*:: public Singleton*/
{
public:
	void testSpi(Mediator *mediator, Spi *spi);
	static Spi* instance();
	void readWriteData();
	void clearString();
	void addDataString();
	void extractDataString();
	void extractEncoder();
	void majCar();
	void printStringSpi();
	void *thSpi(void* arg);

private:
	Spi();
	Mediator *m_mediator;
	static Spi *s_instance;

	unsigned char lenght_string;
	unsigned char* string_spi;

	//** THREAD
	pthread_t th_spi;

};

#endif
