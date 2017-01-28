
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
void testCap2(Mediator* mediator,Navigation* navigation){
	float cap;
	while(1){
		cap = mediator->getHeadingImu();
		cout << " ze cap :" << cap <<endl;
		usleep(100000);
	}	
}

void testCap(Mediator* mediator,Navigation* navigation)
{
	double long_start;
	double lat_start;
	double long_end;
	double lat_end;
	
	//double long_now;
	//double lat_now;

	double lat_error;
	double long_error;

	float cap_start;
	float cap_cible = 0;
	float distance_old;
	float distance_reel = 0;
	unsigned char dir = 0;
	float new_distance = 0;

	double a;

	mediator->addPwmMotorBack(0);
	mediator->addStateSteeringWheel(12);

	// Update distance counter from car
	distance_old = mediator->getDistance();
	cout << " Distance_old = " << distance_old << "m" << endl;
  	
	// Update start Gps position
			cout<< "GPS FIX (cin)" << endl;
	//		cin >> a;
			lat_start = 43.570347;
			long_start = 1.466058;
			cout << " GPS start TH, Lat:" << lat_start << " - Long:"<< long_start << endl;
			mediator->getLatitude();
			cout << "GPS start RE, Lat:" << mediator->getLatitude() << "Long:"<< mediator->getLongitude() << endl;
			lat_error = lat_start-mediator->getLatitude();
			long_error = long_start-mediator->getLongitude();
			cout << " GPS error, Lat:" << lat_error << " - Long:"<< long_error << endl;
	// Switch Gps acquisition mode
			mediator->addModeGps(1);
	// Update end Gps position
			lat_end = 43.570791;
			long_end = 1.466920;
			cout << " GPS end TH, Lat:" << lat_end << " - Long:"<< long_end << endl;

	// Update actual position of the car on the map ??
			//navigation->m_map->SetPosition(long_start, lat_start);
	// update destination of the car on the map ??
			//navigation->m_map->SetDestinationManually(long_end,lat_end);
	
	cout << "Pause avant start regul (cin)" << endl;
	//cin >> a;
	cap_start = mediator->getHeadingImu();
	cout << "cap start : " << cap_start << '\n';	
	do
	{	//cout << " Start moteur" << endl;
		//mediator->addPwmMotorBack(30);
		//while((mediator->getDistance()-distance_old)<=3.0)
		//{
		//	usleep(100);
		//}
		//cout << "Stop moteur" << endl;
		//mediator->addPwmMotorBack(0);
		//distance_reel = mediator->getDistance()-distance_old;
		//cout << "distance 3m = " << distance_reel<<endl;
	// Update distance counter from car
		//distance_old = mediator->getDistance();
				//cout<< "GPS FIX (cin)" << endl;
				//cin >> a;
				//cout << "latitude :";
				//cin >> lat_now;
				//cout << endl;

				//cout << "longitude :";
				//cin >> long_now;
				//cout << endl;

				//cout << "GPS now RE, Lat:" << mediator->getLatitude() << "Long:"<< mediator->getLongitude() << endl;
				//cout << "GPS now CORECT, Lat:" << mediator->getLatitude()+lat_error << "Long:"<< mediator->getLongitude()+long_error << endl;
				//cout << "tempo (cin)"<< endl;
				//cin >> a;
		// Update actual position of the car on the map
				//navigation->m_map->SetPosition(mediator->getLongitude()+long_error, mediator->getLatitude()+lat_error);
				//navigation->m_map->SetPosition(long_now, lat_now);
		// Update new cap
				//cap_cible = navigation->m_map->GetCorrectiveHeading(5.0);
		//cout << "Cap cible calculé :" << cap_cible << endl;
		//usleep(1000000);	
		float capReel = mediator-> getHeadingImu();
		cap_cible = capReel - cap_start;
		if(cap_cible<-180.0) cap_cible += 360.0;
		if(cap_cible > 180.0) cap_cible -=360.0;
		//cout << "Cap Reel : "<< capReel << "   Correction :" << cap_cible<<endl;
		
		//cin >> cap_cible;
		//new_distance = navigation->m_map->GetFrontAndTurnDistance(cap_cible);
		//dir = navigation->m_map->GetFront();
		//cout << "Direction :" << (int)dir << " sur " << new_distance<< "m"<<endl;
		//cout << "temp (cin)" << endl;
		//cin >> a;
		//usleep(1000000);
		//cout << "Set Direction" << endl;
		if(cap_cible <= 2 && cap_cible >=-2)
			dir =  13;
		if(cap_cible <=4 && cap_cible >2)
			dir =  12;
		if(cap_cible <=6 && cap_cible >4)
			dir =  11;
		if(cap_cible <=8 && cap_cible >6)
			dir =  10;
		if(cap_cible <=10 && cap_cible >8)
			dir =  9;
		if(cap_cible <=12 && cap_cible >10)
			dir =  8;
		if(cap_cible <=14 && cap_cible >12)
			dir =  7;
		if(cap_cible <=16 && cap_cible >14)
			dir =  6;
		if(cap_cible <=18 && cap_cible >16)
			dir =  5;
		if(cap_cible <=20 && cap_cible >18)
			dir =  4;
		if(cap_cible <=24 && cap_cible >20)
			dir =  3;
		if(cap_cible <=179 && cap_cible >24)
			dir =  2;

		if(cap_cible <-2 && cap_cible >=-4)
			dir =  14;
		if(cap_cible <-4 && cap_cible >=-6)
			dir =  15;
		if(cap_cible <-6 && cap_cible >=-8)
			dir =  16;
		if(cap_cible <-8 && cap_cible >=-10)
			dir =  17;
		if(cap_cible <-10 && cap_cible >=-12)
			dir =  18;
		if(cap_cible <-12 && cap_cible >=-14)
			dir =  19;
		if(cap_cible <-14 && cap_cible >=-16)
			dir =  20;
		if(cap_cible <-16 && cap_cible >=-18)
			dir =  21;
		if(cap_cible <-18 && cap_cible >=-20)
			dir =  22;
		if(cap_cible <-20 && cap_cible >=-24)
			dir =  23;
		if(cap_cible <-24 && cap_cible >=-180)
			dir =  24;

		//if(cap_cible >2)
		//	dir=dir-3;
		//if(cap_cible <-2)
		//	dir=dir+3;


		cout <<" dir : "<< (int)dir << endl;
		mediator->addStateSteeringWheel(dir);
		usleep(100000);
		//cout << "temp (cin)" << endl;
		//cin >> a;
		//cout << "Start moteur" << endl;
		//mediator->addPwmMotorBack(30);
		/*while((mediator->getDistance()-distance_old)<=new_distance)
		{
			usleep(100);
		}
		cout << "Stop moteur" << endl;
		mediator->addPwmMotorBack(0);
		distance_reel = mediator->getDistance()-distance_old;
		cout << "distance " << new_distance <<"m = " << distance_reel<<endl;
		
		// Update distance counter from car
		distance_old = mediator->getDistance();
		usleep(1000000);
		mediator->addStateSteeringWheel(12);
		usleep(1000000);
		// Update actual position of the car on the map ??
				//navigation->m_map->SetPosition(mediator->getLongitude()+long_error, mediator->getLatitude()+lat_error);		
		*/	
		/*cout << "latitude :";
		cin >> lat_now;
		cout << endl;

		cout << "longitude :";
		cin >> long_now;
		cout << endl;
		navigation->m_map->SetPosition(long_now, lat_now);
		*/	
	}while(navigation->m_map->DirectDistance(mediator->getLatitude()+lat_error,mediator->getLongitude()+long_error,lat_end,long_end)>=2.0);
	//}while(navigation->m_map->DirectDistance(lat_now,long_now,lat_end,long_end)>=2.0);	
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
		usleep(1000000);
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
				case 't' : 
					testCap(mediator, navigation);
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

	Imu* imu;
	imu = Imu::instance();

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
