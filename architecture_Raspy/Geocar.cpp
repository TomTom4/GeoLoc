#include "Geocar.h"

using namespace std;

	//Add your methodes over here 

void testSpi(Mediator *mediator,Spi *spi){

	mediator->printModel();
	//PARAMETRAGE BIB WIRINGPI
	wiringPiSetup ();

	//PARAMETRAGE SPI
	wiringPiSPISetup(0,1000000);
	//	fprintf("SPI Setup failed ");

	mediator.printModel();

	for(int i=0;i<1000;i++)
	{
		mediator.addPwmMotorBack(30);
		spi.majCar();
		mediator.printEncodeur();
		delay(1000);
		cout << endl;
	}
	mediator.addPwmMotorBack(0);
	spi.majCar();

  /*for(i=0;i<=50;i=i+5)
  {
    tutur.addData(1,i);
    //cout << "\t\t MajCar "<< endl << endl;
    com.majCar();
    tutur.printEncodeur();
    delay(100);
  }
  for(i=50;i>=0;i=i-5)
  {
    tutur.addData(1,i);
    //cout << "\t\t MajCar "<< endl << endl;
    com.majCar();
    tutur.printEncodeur();

    delay(100);
  }
  delay(500);
  tutur.addData(2,2);
  com.majCar();*/
}
	
}

int main(){
	Controler *controler;
	Mediator *mediator;
	Spi *spi;
	
	mediator = Mediator::instance();
	controler = Controler::instance();
	spi = Spi::instance();

	//temporary :only to test of spi
	testSpi(mediator, spi);
	return 0;
}
