#ifndef DEF_GPS_HANDLER
#define DEF_GPS_HANDLER

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cmath>
#include <iostream>
#include <thread>
#include <pthread.h>

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
		double ToRadians(double degrees);
		//** THREAD
		void* thGps(void);
		static void* thGpsHelper(void* context);

	private:
		//** SINGLETON
		Gps();
		Mediator* m_mediator;
		static Gps* s_instance;
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
		pthread_t th_gps;
};
#endif
