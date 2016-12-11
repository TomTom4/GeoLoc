
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
	// acquisition position départ
	gps->updatePos();
	long_start = gps->getLong();
	lat_start = gps->getLat();

	// update actual position of the car
	SetPosition(long_start, lat_start);
	// update end destination
	SetDestination(long_end,lat_end);
	delay(3000);
	// start moteurs
	move_car->moveFront();
	do
	{
		// No action, update mesure1 & mesure2 from spi
		move_car->rien();
		disatance = spi->spiGetMesure2();
		if((disatance - distance_old)>= 5.0)
		{
			// stop moteur
			move_car->stopFrontBack();
			move_car->rien();
			disatance = spi->spiGetMesure2();
			distance_old = disatance;
			// delay for gps fix
			delay(5000);
			// get gps position
			gps->updatePos();
			// update actual position of the car from GPS !
			SetPosition(gps->getLong(),gps->getLat());
			// Find new cap
			cap_cible = CapAlgorithm();

			if(cap_cible > 0 )
			{ // turn left
				move_car->moveLeft();
				//delay(??);
			}
			else
			{ // turn right
				move_car->moveRight();
				//delay(??); // for front wheel
			}
			move_car->moveFront();
			//delay(??); // function of cap_cible ?
			move_car->stopFrontBack();
			move_car->center();
			// delay(??); // for center
		}
	}while(!test_fin());
}
