#ifndef DEF_GPS_HANDLER
#define DEF_GPS_HANDLER

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cmath>
#include <iostream>
#include <thread>

#include <string>
#include <vector>
#include <fstream>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include <math.h>

#include "minmea.h"
#include "Mediator.h"

class Gps{

	public:
		//** SINGLETON
		static Gps* instance();
		//** METHODS
    void readLineFromGps();
    void updatePos();
    double getLong();
    double getLat();
		double DirectDistance(double lat1, double lng1, double lat2, double lng2);
		//** THREAD
		void thGps(void);

	private:
		//** SINGLETON
		Gps();
		Mediator *m_mediator;
		static Gps *s_instance;
		//** ATTRIBUTES
		double longitude;
	  double latitude;
		double degre,minute,second;
		int nb_satellites;
		struct minmea_sentence_gga frame_gga;
		struct minmea_sentence_rmc frame_rmc;
		char buffer[1024];
		int fd;
		//** ERROR
		int result_code;
		//** THREAD
		thread *th_gps;
};
#endif
