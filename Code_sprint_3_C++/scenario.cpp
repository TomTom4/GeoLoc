
#include <wiringPi.h>
#include <stdlib.h>
#include "gps.h" 
#include "spi.h" 
#include "scenario.h" 

Scenario::Scenario(Gps* gps_sc, Spi* spi_sc)
{
	gps = gps_sc;
	spi = spi_sc;
	coef_long = 0.080564;
	coef_lat = 0.111194;
	long_end = 43.5708618;
	lat_end = 1.4670463;
	x_end = long_end*coef_long;
	y_end = lat_end*coef_lat;
}

void Scenario::start(void)
{
	// INIT
	
	// acquisition position départ
	gps->updatePos();
	long_start = gps->getLong();
	lat_start = gps->getLat();

	// Conversion dans le plan xy
	x_start = long_start*coef_long;
	y_start = lat_start*coef_lat;
	x_end = x_end - x_start;
	y_end = y_end - y_start;

	// position courant
	x = x_start - x_start;
	y = y_start - y_start;
	
	delay(3000);
	do
	{
	//Start moteur
	if(mesure >= 5)
	{
		// stop moteur
		delay(5000);
		gps->updatePos();
		x_gps = gps->getLong()*coef_long-x_start;
		y_gps = gps->getLat()*coef_lat-y_start;
		// calcul cap vers point de fin
		cap_fin = 0;
		// calcul cap vers point gps
		cap_gps = 0;
		cap_cible = abs(cap_gps - cap_fin);
		x = 0;
		y = 0;
		if( cap_cible == 0)
		{
		}	// tourne gauche
		else
		{
		}	// tourne droit
	}
		
	}while(x > (x_end+1) && x < (x_end-1) && y > (y_end+1) && y < (y_end-1));
}
