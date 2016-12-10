#ifndef _SCENARIO_H
#define _SCENARIO_H


class Scenario
{
	private:
	double long_start;
	double lat_start;
	double long_end;
	double lat_end;
	
	double x_start;
	double y_start;
	double x_end;
	double y_end;
	double x,y;
	double x_gps, y_gps;

	double coef_long;
	double coef_lat;

	double cap_cible, cap_fin, cap_gps;

	double mesure;

	Gps* gps;
	Spi* spi;
	public:
	Scenario(Gps* gps_sc, Spi* spi_sc);
	void start();
};

#endif