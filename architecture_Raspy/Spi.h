#ifndef DEF_SPI
#define DEF_SPI

#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>

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
	//** SINGLETON
	static Spi* instance();
	//** METHODS
	void readWriteData();
	void clearString();
	void addDataString();
	void extractDataString();
	void extractEncoder();
	void majCar();
	void printStringSpi();
	//** THREAD
	void* thSpi(void);
	static void* thSpiHelper(void *context);

private:
	//** SINGLETON
	Spi();
	Mediator *m_mediator;
	static Spi *s_instance;

	//** ATTRIBUTES
	unsigned char lenght_string;
	unsigned char* string_spi;

	//** ERROR
	int result_code;
	//** THREAD
	pthread_t th_spi;
};

#endif
