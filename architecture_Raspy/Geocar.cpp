
#include <string>
#include <stdio.h>// c'est pas la même que iostream?
#include <iostream>
#include <tuple>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "Mediator.h"
#include "Controler.h"
#include "Spi.h"
#include "GpsHandler.h"
#include "Navigation.h"
#include "Geocar.h"

using namespace std;

	//Add your methodes over here

void testSpi(Mediator *mediator, Spi *spi){

	mediator->printModel(); // State of the car
	cout << " On avance !" << endl;
	mediator->addPwmMotorBack(30);
	usleep(2000000);
	cout << " On stop !" << endl;
	mediator->addPwmMotorBack(0);
	usleep(2000000);
	cout << " On tourne à gauche !" << endl;
  mediator->addStateSteeringWheel(6);
  usleep(2000000);
	cout << " On avance !" << endl;
	mediator->addPwmMotorBack(30);
	usleep(2000000);
	cout << " On stop !" << endl;
	mediator->addPwmMotorBack(0);
	usleep(2000000);
	cout << " On centre !" << endl;
  mediator->addStateSteeringWheel(12);
  usleep(2000000);
	cout << " On avance !" << endl;
	mediator->addPwmMotorBack(30);
	usleep(2000000);
	cout << " On stop !" << endl;
	mediator->addPwmMotorBack(0);
	usleep(2000000);
	cout << " On tourne à droite !" << endl;
  mediator->addStateSteeringWheel(18);
  usleep(2000000);
	cout << " On avance !" << endl;
	mediator->addPwmMotorBack(30);
	usleep(2000000);
	cout << " On stop !" << endl;
	mediator->addPwmMotorBack(0);
	usleep(2000000);
	cout << " On recule!" << endl;
	mediator->addPwmMotorBack(30+128);
	usleep(2000000);
	cout << " On stop !" << endl;
	mediator->addPwmMotorBack(0);
	usleep(2000000);

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

int testNavigation(){

	//rapidxml::file<> xmlFile("heavy.osm");
	Map MyMap("heavy.osm");

	std::vector<tuple<string, double>> MyVectorOfUserDestination = MyMap.GetTupleOfDestinations();

	double ExamplePointLat = 43.570358;
	double ExamplePointLon =  1.466047;

	//double ExampleDestLat = 43.5708618;
	//double ExampleDestLon = 1.4670463;
	MyMap.SetPosition(ExamplePointLon,ExamplePointLat);
	MyMap.SetDestination(-1858);
	//MyMap.WhichRoadWithLatLon();

	MyMap.Display(0);
	MyMap.Display(1);

	MyMap.SetPosition(1.466078, 43.570376);
	std::cout << "GetCorrectiveHeading(3) : " << MyMap.GetCorrectiveHeading(3.0) << '\n';

	MyMap.Display(1);

	MyMap.SetPosition(1.466117,43.570386);
	std::cout << "GetCorrectiveHeading(3) : " << MyMap.GetCorrectiveHeading(3.0) << '\n';

	MyMap.Display(1);

/*
	MyMap.CreateAll(0, MyMap.image);
	MyMap.DisplayMyPosition();
	MyMap.DisplayImage(0);

	MyMap.CreateAll(1, MyMap.imageClose);
	MyMap.DisplayCloseMyPosition();
	MyMap.DisplayImage(1);
*/
/*
	// new

	double CurrentClosestNode = MyMap.GetClosestNode()->GetId();

	// Zepeng Code

	Router MyRouter;

	std::vector<char*> ipath;

	//char pointA[7] = "-1630";
	char pointA [10];
	// Need to remove the decimals
	sprintf (pointA, "%.0f", CurrentClosestNode);
	std::cout << "Current closest node : " << pointA << '\n';
	char pointB[7] = "-1858";

	std::cout << "From : " << pointA << " ... to : " << pointB << '\n';
	ipath = MyRouter.getpath(pointA,pointB);
	int len = ipath.size();
	std::cout << "ipath length : " << len << '\n';

	// End Zepeng Code //

	MyMap.SetPath(ipath);
	std::cout << "The cap to follow : " << MyMap.CapAlgorithm() << '\n';
	MyMap.DisplayPath(0, MyMap.image);
	MyMap.DisplayImage(0);
*/
	return 1;
}


int main(){

	cout << "dans le main" << endl << flush;

	//PARAMETRAGE BIB WIRINGPI
	wiringPiSetup ();

	//PARAMETRAGE SPI
	wiringPiSPISetup(0,1000000);

	Mediator *mediator = NULL;
	mediator = Mediator::instance();
	
	Spi *spi;
	spi = Spi::instance();
	
	//Navigation *navigator;
	//navigator = Navigation::instance();

	//Controler *controler;
	//controler = Controler::instance();
	
	Gps *gps;
	gps = Gps::instance();

	//testSpi(mediator, spi);
	//testKey(mediator,spi,gps);
	while(1)
	{
		usleep(1000000);
		cout << " main "<< endl;
	}
	return 0;
}
