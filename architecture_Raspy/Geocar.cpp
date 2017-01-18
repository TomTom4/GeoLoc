
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
#include "parserV1.hpp"
#include "kbhit.h"
#include "music.h"

using namespace std;

void testCap(Mediator* mediator,Navigation* navigation)
{
	double long_start;
	double lat_start;
	double long_end;
	double lat_end;
	float cap_cible = 0;
	float distance_old;
	unsigned char dir = 0;
	float new_distance = 0;

	mediator->addPwmMotorBack(0);
	mediator->addStateSteeringWheel(12);
	// Update distance counter from car
	distance_old = mediator->getDistance();
	cout << " Init distance: " << distance_old << "m" << endl;
  // Update start Gps position
	long_start = mediator->getLongitude();
	lat_start = mediator->getLatitude();
	// Switch Gps acquisition mode
	mediator->addModeGps(1);
	// Update end Gps position
	long_end = 1.4670463;
	lat_end = 43.5708618;
	cout << "Init position GPS start, Long:" << long_start << "Lat:"<< lat_start << endl;
	cout << "Init position GPS end, Long:" << long_end << "Lat:"<< lat_end << endl;

	// Update actual position of the car on the map ??
		navigation->m_map->SetPosition(long_start, lat_start);
	// update destination of the car on the map ??
		navigation->m_map->SetDestinationManually(long_end,lat_end);
	usleep(3000000);
	do
	{
		cout << " Start moteur" << endl;
		mediator->addPwmMotorBack(30);
		while((mediator->getDistance()-distance_old)>=5.0)
		{
			usleep(100);
		}
		cout << "Stop moteur" << endl;
		mediator->addPwmMotorBack(0);
		// Update distance counter from car
		distance_old = mediator->getDistance();
		cout<< "GPS FIX" << endl;
		usleep(3000000);
		mediator->printGps();
		// Update actual position of the car on the map ??
			navigation->m_map->SetPosition(mediator->getLongitude(), mediator->getLatitude());
		// Update new cap
			cap_cible = navigation->m_map->GetCorrectiveHeading(5.0);
		cout << "Cap cible calculé :" << cap_cible << endl;
			new_distance = navigation->m_map->GetFrontAndTurnDistance(cap_cible);
			dir = navigation->m_map->GetFront();
		cout << "Direction :" << (int)dir << " sur " << new_distance<< "m"<<endl;
			
		delay(3000000);
		cout << "Vers la Gauche" << endl;
		mediator->addStateSteeringWheel(dir);
			usleep(2000000);
		distance_old = mediator->getDistance();
		while((mediator->getDistance()-distance_old)>=new_distance)
		{
			usleep(100);
		}
		cout << "Stop moteur" << endl;
		mediator->addPwmMotorBack(0);
		// Update distance counter from car
		distance_old = mediator->getDistance();
		usleep(2000000);
		mediator->addStateSteeringWheel(12);
		usleep(2000000);
		// Update actual position of the car on the map ??
			navigation->m_map->SetPosition(mediator->getLongitude(), mediator->getLatitude());		
	}while(navigation->m_map->DirectDistance(mediator->getLatitude(),mediator->getLongitude(),lat_end,long_end)>=2.0);
	cout << " VALIDATION OBJECTIF !!!!!!!!! GRANDE VALIDATION !!!!!" << endl;
}

void testSpi(Mediator *mediator){

	mediator->printModel(); // State of the car
	usleep(2000000);
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

void manuel(Mediator *mediator,Navigation* navigation)
{
	char touche;
	int cpt;
	//INSTRUCTIONS DE PILOTAGE
	printf("\n\n");
	printf("Front = o \n");
	printf("Left = k \n");
	printf("Back = l \n");
	printf("Right = m \n");

	printf("Stop = p \n");

	printf("Music = a \n");
	printf("GPS = g \n");
	printf("Test Mvt = w \n");
	printf("Test Cap = x \n");
	printf("Test Wheel Regulation = j \n");
	printf("End Prog = e \n\n");

	while(1)
	{
		usleep(250000);
		if(kbhit())
		{
			touche = getchar();
			switch(touche)
			{
				case 'o': // Devant
				case 65 :// key up
					mediator->addPwmMotorBack(30);
					break;

				case 'k': // Gauche
				case 68 :// key left
					if(mediator->getStateSteeringWheel() == 12)
					{
						mediator->addStateSteeringWheel(6);
					}
					else
					{
						if(mediator->getStateSteeringWheel() == 18)
						{
							mediator->addStateSteeringWheel(12);
						}
					}
					break;

				case 'l': // Derriere
				case 66 :// key down
					mediator->addPwmMotorBack(30+128);
					break;

				case 'm':// Droite
				case 67 :// key right
					if(mediator->getStateSteeringWheel() == 12)
					{
						mediator->addStateSteeringWheel(18);
					}
					else
					{
						if(mediator->getStateSteeringWheel() == 6)
						{
							mediator->addStateSteeringWheel(12);
						}
					}
					break;

				case 'p' : // Stop front back
				case '\n':
					mediator->addPwmMotorBack(0);
					break;

				case 'e' : //Fin
					mediator->addPwmMotorBack(0);
					mediator->addStateSteeringWheel(12);
					exit(1);
					break;

				case 'a': //Music
					cpt = mediator->getCptMusic();
					cpt++;
					if(cpt == 5)
						cpt = 1;
					mediator->addCptMusic(cpt);
					break;

				case 'z': //Stop Music
					mediator->addCptMusic(0);
					break;

				case 'g': // GPS
					mediator->printGps();
					break;

				case 'w': // Scenario
					testSpi(mediator);
					break;

				case 'x': // Scenario
					testCap(mediator,navigation);
					break;

			}// SWITCH
		}//KBHIT
	}//WHILE
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



int main()
{
	//PRESENTATION
	printf("\t\n\n\n");
	printf("\t\t    _/    _/  _/      _/  _/_/_/    _/_/_/  _/    _/  _/_/_/_/_/\n");
	printf("\t\t   _/  _/    _/_/    _/    _/    _/        _/    _/      _/     \n");
	printf("\t\t  _/_/      _/  _/  _/    _/    _/  _/_/  _/_/_/_/      _/      \n");
	printf("\t\t _/  _/    _/    _/_/    _/    _/    _/  _/    _/      _/       \n");
	printf("\t\t_/    _/  _/      _/  _/_/_/    _/_/_/  _/    _/      _/        \n\n\n");

	//PARAMETRAGE BIB WIRINGPI
	wiringPiSetup ();

	//PARAMETRAGE SPI
	wiringPiSPISetup(0,1000000);

	Mediator *mediator = NULL;
	mediator = Mediator::instance();

	Spi* spi;
	spi = Spi::instance();

	Gps* gps;
	gps = Gps::instance();

	//Music* music;
	//music = Music::instance();

	Navigation* navigation;
	navigation = Navigation::instance();

	//Controler *controler;
	//controler = Controler::instance();

	//testSpi(mediator, spi);
	//testKey(mediator,spi,gps);

	manuel(mediator, navigation);
	while(1)
	{
		usleep(1000000);
		cout << " main "<< endl;
	}
	return 0;
}
