#ifndef DEF_SPI
#define DEF_SPI

#include <thread>

#include "Model.h"
#include "const.hpp"
#include "Mediator.h"

using namespace std;

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
	void* thGps(void);
	static void* thGpsHelper(void* context);
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
