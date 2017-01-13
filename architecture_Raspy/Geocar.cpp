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

	mediator->printModel(); // State of the car
	cout << " On avance !" << endl;
	mediator->addPwmMotorBack(30);
	usleep(2000);
	cout << " On stop !" << endl;
	mediator->addPwmMotorBack(0);
	usleep(2000);
	cout << " On tourne à gauche !" << endl;
  mediator->addStateSteeringWheel(6);
  usleep(2000);
	cout << " On avance !" << endl;
	mediator->addPwmMotorBack(30);
	usleep(2000);
	cout << " On stop !" << endl;
	mediator->addPwmMotorBack(0);
	usleep(2000);
	cout << " On centre !" << endl;
  mediator->addStateSteeringWheel(12);
  usleep(2000);
	cout << " On avance !" << endl;
	mediator->addPwmMotorBack(30);
	usleep(2000);
	cout << " On stop !" << endl;
	mediator->addPwmMotorBack(0);
	usleep(2000);
	cout << " On tourne à droite !" << endl;
  mediator->addStateSteeringWheel(18);
  usleep(2000);
	cout << " On avance !" << endl;
	mediator->addPwmMotorBack(30);
	usleep(2000);
	cout << " On stop !" << endl;
	mediator->addPwmMotorBack(0);
	usleep(2000);

}

void testkey(Mediator *mediator, Spi *spi, Gps *gps)
{
	//PARAMETRAGE BIB WIRINGPI
	wiringPiSetup ();
	//PARAMETRAGE SPI
	wiringPiSPISetup(0,1000000);
	//	fprintf("SPI Setup failed ");

	mediator->printModel(); // State of the car
	cout << " On avance !" << endl;
	mediator->addPwmMotorBack(30);
	usleep(2000);
	cout << " On stop !" << endl;
	mediator->addPwmMotorBack(0);
	usleep(2000);
	cout << " On tourne à gauche !" << endl;
  mediator->addStateSteeringWheel(6);
  usleep(2000);
	cout << " On avance !" << endl;
	mediator->addPwmMotorBack(30);
	usleep(2000);
	cout << " On stop !" << endl;
	mediator->addPwmMotorBack(0);
	usleep(2000);
	cout << " On centre !" << endl;
  mediator->addStateSteeringWheel(12);
  usleep(2000);
	cout << " On avance !" << endl;
	mediator->addPwmMotorBack(30);
	usleep(2000);
	cout << " On stop !" << endl;
	mediator->addPwmMotorBack(0);
	usleep(2000);
	cout << " On tourne à droite !" << endl;
  mediator->addStateSteeringWheel(18);
  usleep(2000);
	cout << " On avance !" << endl;
	mediator->addPwmMotorBack(30);
	usleep(2000);
	cout << " On stop !" << endl;
	mediator->addPwmMotorBack(0);
	usleep(2000);

}


int main(){
	//Controler *controler;
	Mediator *mediator;
	Spi *spi;
	Gps *gps

	mediator = Mediator::instance();
	//controler = Controler::instance();
	spi = Spi::instance();
	gps = Gps::instance();

	//temporary :only to test of spi
	testSpi(mediator, spi);
	testKey(mediator,spi,gps);
	/*while(1)
	{
		usleep(1000000);
		cout << " main "<< endl;
	}*/
	return 0;
}
