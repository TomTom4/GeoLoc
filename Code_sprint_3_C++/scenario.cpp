
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
	
	// acquisition position départ
	gps->updatePos();
	long_start = gps->getLong();
	lat_start = gps->getLat();

	SetPosition(long_start, lat_start);
	SetDestination(long_end,lat_end);
	delay(3000);
	move_car->moveFront();
	do
	{
	if(mesure >= 5)
	{
		// stop moteur
		delay(5000);
		gps->updatePos();
		SetPosition(gps->getLong(),gps->getLat());
		cap_cible = CapAlgorithm();
		if(cap_cible > 0 )
		{
			move_car->moveLeft();
		}	// tourne gauche
		else
		{
			move_car->moveRight();
		}	// tourne droit
	}	
	}while(!test_fin());
}
