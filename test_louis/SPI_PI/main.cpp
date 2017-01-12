#include "car.hpp"
#include "spi.hpp"
#include <iostream>

#include <wiringPi.h>
#include <wiringPiSPI.h>

using namespace std;


int main()
{
  Car car_main;
  Spi spi_main(&car_main);

	//PARAMETRAGE BIB WIRINGPI
	wiringPiSetup ();

	//PARAMETRAGE SPI
	wiringPiSPISetup(0,10000);
	//	fprintf("SPI Setup failed ");

	car_main.printCar();

	for(int i=0;i<1000;i++)
	{
		car_main.addPwmMotorBack(30);
		spi_main.majCar();
		car_main.printEncodeur();
		delay(1000);
		cout << endl;
	}
	car_main.addPwmMotorBack(0);
	spi_main.majCar();

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
