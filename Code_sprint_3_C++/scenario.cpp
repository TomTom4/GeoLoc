
#include <wiringPi.h>
#include <stdlib.h>
#include "minmea.h"
#include "gps.h"
#include "spi.h"
#include "move_car.h"
#include "scenario.h"
#include "carmodel.hpp"

Scenario::Scenario(Gps* gps_sc, Spi* spi_sc, MoveCar* move_car_sc)
{	gps = gps_sc;
	spi = spi_sc;
	move_car = move_car_sc;
	long_end = 43.5708618;
	lat_end = 1.4670463;
}

void Scenario::start(void)
{
	// INIT
	float distance_old;
	float disatance;

	// No action, update mesure1 & mesure2 from spi
	move_car->rien();
	distance_old = spi->spiGetMesure2();
	cout << " Init compteur codeur : " << distance_old << "m" << endl;
	// acquisition position départ
	gps->updatePos();
	long_start = gps->getLong();
	lat_start = gps->getLat();
	cout << "Init position GPS start, Long:" << long_start << "Lat:"<< lat_start << endl;
	cout << "Init position GPS end, Long:" << long_end << "Lat:"<< lat_end << endl;
	// update actual position of the car
	SetPosition(long_start, lat_start);
	// update end destination
	SetDestination(long_end,lat_end);
	delay(3000);
	// start moteurs
	cout << " Start moteur" << endl;
	move_car->moveFront();
	do
	{
		// No action, update mesure1 & mesure2 from spi
		move_car->rien();
		disatance = spi->spiGetMesure2();
		cout << "delta distance = "<< distance - distance_old << endl;
		if((disatance - distance_old)>= 5.0)
		{
			// stop moteur
			cout << "Stop moteur" << endl;
			move_car->stopFrontBack();
			move_car->rien();
			disatance = spi->spiGetMesure2();
			cout << "Distance 5m mesurée = "<< distance - distance_old << endl;
			distance_old = disatance;
			// delay for gps fix
			cout<< "GPS FIX" << endl;
			delay(5000);
			// get gps position
			gps->updatePos();
			// update actual position of the car from GPS !
			cout << "Position GPS mesurée, Long:" <<gps->getLong() << "Lat:"<< gps->getLat() << endl;
			SetPosition(gps->getLong(),gps->getLat());
			// Find new cap
			cap_cible = CapAlgorithm();
			cout << "Cap cible calculé :" << cap_cible << endl;
			delay(20000);

			if(cap_cible > 0 )
			{ // turn left
				cout << "Vers la Gauche" << endl;
				move_car->moveLeft();
				//delay(??);
			}
			else
			{ // turn right
				cout << "Vers la Droite" << endl;
				move_car->moveRight();
				//delay(??); // for front wheel
			}
			cout << " Start moteur" << endl;
			move_car->moveFront();
			//delay(??); // function of cap_cible ?
			move_car->stopFrontBack();
			cout << " Stop moteur" << endl;
			move_car->center();
			// delay(??); // for center
			cout << " Direction centrée" << endl;
			delay(3000);
			cout << " Start moteur" << endl;
			move_car->moveFront();
		}
	}while(!test_fin());
	cout << " VALIDATION OBJECTIF !!!!!!!!! GRANDE VALIDATION !!!!!" << endl;
}
