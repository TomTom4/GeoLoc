#ifndef DEF_GPS_HANDLER
#define DEF_GPS_HANDLER

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cmath>

#include "minmea.h"

class GpsHandler{

	public:
		//** SINGLETON
		static Gps* instance();
		//** METHODS
    void readLineFromGps();
    void updatePos();
    double getLong();
    double getLat();
		//** THREAD
		void* thGps(void);
		static void* thGpsHelper(void *context);

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
		pthread_t th_gps;
};
#endif
