#include "Spi.h"

using namespace std;

Spi *Spi::s_instance = 0;

	//Add your methodes over here 
	Spi::Spi(){}
	Spi* Spi::instance(){
		if(!Spi::s_instance)
			Spi::s_instance = new Spi();
			Spi::s_instance->m_mediator = Mediator::instance();
		return Spi::s_instance;	
	}

	void spiReadWriteData();
	void spiClearString();
	void spiAddData();
	void extractData();
	void spiMajCar();
