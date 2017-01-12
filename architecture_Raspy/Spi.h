#ifndef DEF_SPI
#define DEF_SPI

#include <iostream>
#include <stdio.h>
#include <string>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "Model.h"
#include "Spi.h"
#include "const.hpp"



#include "Mediator.h"

class Spi /*:: public Singleton*/
{
public:
	static Spi* instance();	
	void readWriteData();
	void clearString();
	void addDataString();
	void extractDataString();
	void extractEncodeur();
	void majCar();
	void printStringSpi();

private: 
	Spi();
	Mediator *m_mediator;
	static Spi *s_instance;

	unsigned char lenght_string;
	unsigned char* string_spi;
};

#endif
