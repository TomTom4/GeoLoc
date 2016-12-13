
#include <wiringPi.h>
#include <stdlib.h>
#include <iostream>
#include "minmea.h"
#include "gps.h"
#include "spi.h"
#include "move_car.h"
#include "scenario.h"
#include "carmodel.hpp"

using namespace std;

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
	if(0)
	{
	move_car->rien();
	distance_old = spi->spiGetMesure2();
	cout << " Init compteur codeur : " << distance_old << "m" << endl;
	cout << " turn left 5s" << endl;
	move_car->moveLeft();
	delay(5000);
	cout << " Start moteur" << endl;
	move_car->moveFront();
	while(distance - distance_old < 0.05)
	{
		delay(500);
		move_car->rien();
		distance = spi->spiGetMesure2();
		//printf("delta distance = %f\n",(distance - distance_old));
	}
	move_car->stopFrontBack();
	move_car->stopFrontBack();
	move_car->stopFrontBack();
	cout << "Stop 2s" << endl;
	delay(5000);
	move_car->center();
	move_car->center();
	move_car->center();
	cout << "Centrage 2s" << endl;
	delay(5000);
	move_car->moveFront();
	move_car->moveFront();
	move_car->moveFront();
	cout << "start front 2s" << endl;
	delay(5000);
	move_car->stopFrontBack();
	move_car->stopFrontBack();
	move_car->stopFrontBack();
	cout << "STOP POUR 15s" << endl;
	delay(15000);
	
	
	move_car->rien();
	distance_old = spi->spiGetMesure2();
	cout << " Init compteur codeur : " << distance_old << "m" << endl;
	cout << " turn left 5s" << endl;
	move_car->moveLeft();
	delay(5000);
	cout << " Start moteur" << endl;
	move_car->moveFront();
	while(distance - distance_old < 0.10)
	{
		delay(50);
		move_car->rien();
		distance = spi->spiGetMesure2();
		printf("delta distance = %f\n",(distance - distance_old));
	}
	move_car->stopFrontBack();
	cout << "Stop 2s" << endl;
	delay(2000);
	move_car->center();	
	cout << "Centrage 2s" << endl;
	delay(2000);
	move_car->moveFront();
	cout << "start front 2s" << endl;
	delay(2000);
	move_car->stopFrontBack();
	cout << "STOP POUR 15s" << endl;
	delay(15000);


	move_car->rien();
	distance_old = spi->spiGetMesure2();
	cout << " Init compteur codeur : " << distance_old << "m" << endl;
	cout << " turn left 5s" << endl;
	move_car->moveLeft();
	delay(5000);
	cout << " Start moteur" << endl;
	move_car->moveFront();
	while(distance - distance_old < 0.20)
	{
		delay(100);
		move_car->rien();
		distance = spi->spiGetMesure2();
		printf("delta distance = %f\n",(distance - distance_old));
	}
	move_car->stopFrontBack();
	cout << "Stop 2s" << endl;
	delay(2000);
	move_car->center();
	cout << "Centrage 2s" << endl;
	delay(2000);
	move_car->moveFront();
	cout << "start front 2s" << endl;
	delay(2000);
	move_car->stopFrontBack();
	cout << "STOP POUR 15s" << endl;
	delay(15000);




	move_car->rien();
	distance_old = spi->spiGetMesure2();
	cout << " Init compteur codeur : " << distance_old << "m" << endl;
	cout << " turn right 5s" << endl;
	move_car->moveRight();
	delay(5000);
	cout << " Start moteur" << endl;
	move_car->moveFront();
	while(distance - distance_old < 0.05)
	{
		delay(100);
		move_car->rien();
		distance = spi->spiGetMesure2();
		printf("delta distance = %f\n",(distance - distance_old));
	}

	move_car->stopFrontBack();
	cout << "Stop 2s" << endl;
	delay(2000);
	move_car->center();
	cout << "Centrage 2s" << endl;
	delay(2000);
	move_car->moveFront();
	cout << "start front 2s" << endl;
	delay(2000);
	move_car->stopFrontBack();
	cout << "STOP POUR 15s" << endl;
	delay(15000);
	
	
	move_car->rien();
	distance_old = spi->spiGetMesure2();
	cout << " Init compteur codeur : " << distance_old << "m" << endl;
	cout << " turn right 5s" << endl;
	move_car->moveRight();
	delay(5000);
	cout << " Start moteur" << endl;
	move_car->moveFront();
	while(distance - distance_old < 0.10)
	{
		delay(100);
		move_car->rien();
		distance = spi->spiGetMesure2();
		printf("delta distance = %f\n",(distance - distance_old));
	}
	move_car->stopFrontBack();
	cout << "Stop 2s" << endl;
	delay(2000);
	move_car->center();
	cout << "Centrage 2s" << endl;
	delay(2000);
	move_car->moveFront();
	cout << "start front 2s" << endl;
	delay(2000);
	move_car->stopFrontBack();
	cout << "STOP POUR 15s" << endl;
	delay(15000);


	move_car->rien();
	distance_old = spi->spiGetMesure2();
	cout << " Init compteur codeur : " << distance_old << "m" << endl;
	cout << " turn right 5s" << endl;
	move_car->moveRight();
	delay(5000);
	cout << " Start moteur" << endl;
	move_car->moveFront();
	while(distance - distance_old < 0.20)
	{
		delay(100);
		move_car->rien();
		distance = spi->spiGetMesure2();
		printf("delta distance = %f\n",(distance - distance_old));
	}
	move_car->stopFrontBack();
	cout << "Stop 2s" << endl;
	delay(2000);
	move_car->center();
	cout << "Centrage 2s" << endl;
	delay(2000);
	move_car->moveFront();
	cout << "start front 2s" << endl;
	delay(2000);
	move_car->stopFrontBack();
	cout << "STOP POUR 15s" << endl;
	delay(15000);
	}
	else
	{
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
		delay(500);
		move_car->rien();
		distance = spi->spiGetMesure2();
		printf("\n");
		spi->spiPrint();
		//cout << "delta distance = "<< distance - distance_old << endl;
		if((distance - distance_old)>= 5.0)
		{
			// stop moteur
			cout << "Stop moteur" << endl;
			move_car->stopFrontBack();
			move_car->stopFrontBack();
			move_car->stopFrontBack();
			move_car->stopFrontBack();
			move_car->stopFrontBack();
			move_car->stopFrontBack();
			move_car->stopFrontBack();
			move_car->stopFrontBack();			
			move_car->rien();
			distance = spi->spiGetMesure2();
			cout << "Distance 5m mesure"<< endl;
			spi->spiPrint();
			distance_old = distance;
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
			delay(5000);

			if(cap_cible > 0 )
			{ // turn left
				cout << "Vers la Gauche" << endl;
				move_car->moveLeft();
				move_car->moveLeft();
				move_car->moveLeft();
				move_car->moveLeft();
				move_car->moveLeft();
				move_car->moveLeft();
				//delay();
			}
			else
			{ // turn right
				cout << "Vers la Droite" << endl;
				move_car->moveRight();
				move_car->moveRight();
				move_car->moveRight();
				move_car->moveRight();
				move_car->moveRight();
				//delay(??); // for front wheel
			}
			cout << " Start moteur" << endl;
			move_car->moveFront();
			move_car->moveFront();
			move_car->moveFront();
			move_car->moveFront();
			move_car->moveFront();
			delay(2000); // function of cap_cible ?
			move_car->stopFrontBack();
			move_car->stopFrontBack();
			move_car->stopFrontBack();
			move_car->stopFrontBack();
			move_car->stopFrontBack();
			move_car->stopFrontBack();
			cout << " Stop moteur" << endl;
			delay(2000);
			move_car->center();
			move_car->center();
			move_car->center();
			move_car->center();
			move_car->center();
			move_car->center();
			cout << " Direction centre" << endl;
			delay(2000); // for center
			cout << " Start moteur" << endl; 
			move_car->moveFront();
			move_car->moveFront();
			move_car->moveFront();
			move_car->moveFront();
			move_car->moveFront();
		}
	}while(!test_fin());
	cout << " VALIDATION OBJECTIF !!!!!!!!! GRANDE VALIDATION !!!!!" << endl;
	}
}
