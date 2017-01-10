#include "car.hpp"
#include "spi.hpp"
#include <iostream>

#include <wiringPi.h>
#include <wiringPiSPI.h>

using namespace std;


int main()
{
  Car tutur;
  Spi com(&tutur);

	//PARAMETRAGE BIB WIRINGPI
	wiringPiSetup ();

	//PARAMETRAGE SPI
	if(wiringPiSPISetup(0,1000000)<0)
		//fprintf("SPI Setup failed : %s\n",strerror(errno));
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

	tutur.printCar();
	//delay(5000);
	for(int i=0;i<10;i++)
	{
		tutur.addData(1,30);
		//cout << "\t\t MajCar "<< endl << endl;
		com.majCar();
		/*cout << (float) tutur.encodeur_wheel_back_left_100m << endl;
		cout << (float) tutur.encodeur_wheel_back_left_1m << endl;
		cout << (float) tutur.encodeur_wheel_back_left_1cm << endl;

		cout << (float) tutur.encodeur_wheel_back_right_100m << endl;
		cout << (float) tutur.encodeur_wheel_back_right_1m << endl;
		cout << (float) tutur.encodeur_wheel_back_right_1cm << endl;
		tutur.printEncodeur();*/
		delay(1000);
		cout << endl;
	}
	tutur.addData(1,0);
	com.majCar();


	//tutur.addData();
  //float t =43.1234567890123456789;
  //cout << t << endl;
}
