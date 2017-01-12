#include "car.hpp"
#include "spi.hpp"
#include "navigation.hpp"
#include "gps.hpp"

#include <iostream>

#include <wiringPi.h>
#include <wiringPiSPI.h>

using namespace std;


int main()
{
  Car car_main;
  Spi spi_main(&car_main);
  Gps gps;

	//PARAMETRAGE BIB WIRINGPI
	wiringPiSetup ();

	//PARAMETRAGE SPI
	wiringPiSPISetup(0,1000000);
	//	fprintf("SPI Setup failed ");


	car_main.printCar();
  spi_main.majCar();

  cout << " On avance !" << endl;
  car_main.addPwmMotorBack(30);
  spi_main.majCar();
  delay(3000);
  cout << " On stop !" << endl;
  car_main.addPwmMotorBack(0);
  spi_main.majCar();
  delay(3000);
  cout << " On tourne a gauche !" << endl;
  car_main.addStateSteeringWheel(6);
  spi_main.majCar();
  delay(3000);
  cout << " On avance !" << endl;
  car_main.addPwmMotorBack(30);
  spi_main.majCar();
  delay(3000);
  cout << " On stop !" << endl;
  car_main.addPwmMotorBack(0);
  spi_main.majCar();
  delay(3000);
  cout << " On toune a droite !" << endl;
  car_main.addStateSteeringWheel(18);
  spi_main.majCar();
  delay(3000);
  cout << " On avance !" << endl;
  car_main.addPwmMotorBack(30);
  spi_main.majCar();
  delay(3000);
  cout << " On stop !" << endl;
  car_main.addPwmMotorBack(0);
  spi_main.majCar();
  delay(3000);
  cout << " On centre!" << endl;
  car_main.addStateSteeringWheel(12);
  spi_main.majCar();
  delay(3000);
  cout << " On avance !" << endl;
  car_main.addPwmMotorBack(30);
  spi_main.majCar();
  delay(3000);
  cout << " On stop !" << endl;
  car_main.addPwmMotorBack(0);
  spi_main.majCar();
  delay(3000);

//*************
//** Test navigation
double long_start;
double lat_start;
double long_end = 43.5708618;
double lat_end = 1.4670463;

	float cap_cible;
	//double mesure;
	float distance;
	float distance_old;

cout << " TEST NAVIGATION " << endl;
cout << " On Stop !" << endl;
car_main.addPwmMotorBack(0);
car_main.addStateSteeringWheel(12);
spi_main.majCar();
distance_old = car_main.getDistanceFrontLeft();
cout << "Distance old = " << distance_old << endl;
delay(3000);

car_main.printCar();
delay(2000);

// acquisition position départ
cout << " get GPS position !" << endl;
gps.updatePos();
long_start = gps.getLong();
lat_start = gps.getLat();
cout << "Init position GPS start, Long:" << long_start << "Lat:"<< lat_start << endl;
cout << "Init position GPS end, Long:" << long_end << "Lat:"<< lat_end << endl;

// start moteurs
cout << " On avance !" << endl;
car_main.addPwmMotorBack(30);
spi_main.majCar();
do
{
  // No action, update mesure1 & mesure2 from spi
  delay(100);
  spi_main.majCar();
  distance = car_main.getEncodeurWheelBackLeft();
  car_main.printEncodeur();
  //cout << "delta distance = "<< distance - distance_old << endl;
  if((distance - distance_old)>= 5.0)
  {
    // stop moteur
    cout << "Stop moteur" << endl;
    cout << " On Stop !" << endl;
    car_main.addPwmMotorBack(0);
    spi_main.majCar();
    cout << "Distance 5m mesure"<< endl;
    car_main.printEncodeur();
    distance_old = distance;
    // delay for gps fix
    cout<< "GPS FIX" << endl;
    delay(5000);
    // get gps position
    gps.updatePos();
    // update actual position of the car from GPS !
    cout << "Position GPS mesurée, Long:" <<gps.getLong() << "Lat:"<< gps.getLat() << endl;
    SetPosition(gps.getLong(),gps.getLat());
    // Find new cap
    cap_cible = CapAlgorithm();
    cout << "Cap cible calculé :" << cap_cible << endl;
    delay(5000);

    if(cap_cible > 0 )
    { // turn left
      cout << " On toune a gauche !" << endl;
      car_main.addStateSteeringWheel(6);
      spi_main.majCar();
      delay(3000);
      //delay();
    }
    else
    { // turn right
      cout << " On toune a droite !" << endl;
      car_main.addStateSteeringWheel(18);
      spi_main.majCar();
      delay(3000);
      //delay(??); // for front wheel
    }
    cout << " On avance !" << endl;
    car_main.addPwmMotorBack(30);
    spi_main.majCar();
    delay(2000);
    cout << " On stop !" << endl;
    car_main.addPwmMotorBack(0);
    spi_main.majCar();
    delay(2000);

    cout << " On centre !" << endl;
    car_main.addStateSteeringWheel(12);
    spi_main.majCar();
    delay(3000);

  }
}while(!test_fin());
cout << " VALIDATION OBJECTIF !!!!!!!!! GRANDE VALIDATION !!!!!" << endl;
  
/*for(int i=0;i<200;i++)
	{
		//car_main.addPwmMotorBack(30);
		car_main.addStateSteeringWheel(18);
		spi_main.majCar();
		car_main.printEncodeur();
		delay(100);
		cout << endl;
	}
	car_main.addPwmMotorBack(0);
	spi_main.majCar();*/

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
