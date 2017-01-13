#include "Geocar.h"

using namespace std;

	//Add your methodes over here 

void testSpi(Mediator *mediator, Spi *spi){

	mediator->printModel();
	//PARAMETRAGE BIB WIRINGPI
	wiringPiSetup ();

	//PARAMETRAGE SPI
	wiringPiSPISetup(0,1000000);
	//	fprintf("SPI Setup failed ");

	mediator->printModel();

	for(int i=0;i<100;i++)
	{
		mediator->addPwmMotorBack(30);
		spi->majCar();
		mediator->printEncoder();
		delay(100);
		cout << endl;
	}
	mediator->addPwmMotorBack(0);
	spi->majCar();
}
	

int main(){
	Controler *controler;
	Mediator *mediator;
	Spi *spi;
	
	mediator = Mediator::instance();
	controler = Controler::instance();
	spi = Spi::instance();
	spi->startThread();

	//temporary :only to test of spi
	testSpi(mediator, spi);
	return 0;
}
