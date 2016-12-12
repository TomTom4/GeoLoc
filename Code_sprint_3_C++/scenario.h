#ifndef _SCENARIO_H
#define _SCENARIO_H


class Scenario
{
	private:
	double long_start;
	double lat_start;
	double long_end;
	double lat_end;
	
	float cap_cible;
	double mesure;
	float distance;
	float distance_old;
	Gps* gps;
	Spi* spi;
	MoveCar* move_car;
	public:
	Scenario(Gps* gps_sc, Spi* spi_sc, MoveCar* move_car_sc);
	void start();
};

#endif
