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
#include "GpsHandler.h"

using namespace std;

Gps *Gps::s_instance = 0;//setting s_instance because it is a static attribut.

// this function replace the construtor of the object
Gps *Gps::instance(){
  if(!Gps::s_instance)
    Gps::s_instance = new Gps();
    Gps::s_instance->m_mediator = Mediator::instance();
  return Gps::s_instance;
}

Gps::Gps()
{
  /********************************GPS_INIT*************************************/
  /* Opens the /dev/ttyUSB0 file where GPS data are written                    */
  /* Out : the file descriptor for /dev/ttyUSB0                                */
  /*****************************************************************************/
  cout << "GPS initialisation (0.5s)" << endl;
  fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1)
  {
    cout << "gps.c -> Constructor -> Error opening /dev/ttyUSB0" << endl << flush;
    //exit(1);
  }
  usleep(100000);

  cout << "set baud_rate = 115200" << endl << flush;
  write(fd, "$PMTK251,115200*2C\r\n", 20);  //<CR><LF>
  usleep(100000);

  cout << "set FIX update rate = 5Hz"  << endl << flush;
  write(fd, "$PMTK220,200*0F\r\n", 20);
  usleep(100000);

  cout << "enable RMC & GGA only (send every FIX update)"  << endl << flush;
  write(fd, "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28\r\n", 52);  //<CR><LF>
  usleep(100000);

  //** Init var
  longitude = 0;
  latitude = 0;
  nb_satellites = 0;

  //** Create Thread
  result_code = pthread_create(&th_gps,NULL,thGpsHelper,this);
  if(result_code == 0)
  cout << "Creation Thread Gps - Ok" << endl << flush;
}

void *Gps::thGps(void)
{ // Main program of Gps thread
  while(1)
  {
    usleep(200000);
    Gps::updatePos();
      // cout << "Th Gps" << endl << flush;
  }
}

void *Gps::thGpsHelper(void* context)
{
  return((Gps*)context)->Gps::thGps();
}
  /***************************READ_LINE_FROM_GPS********************************/
/* Get a line from GPS data flow in /dev/ttyUSB0 and returns it into a buffer*/
/* In : the file descriptor for /dev/ttyUSB0                                 */
/* In/Out: the char * buffer where the extracted line is written             */
/*****************************************************************************/

void Gps::readLineFromGps()
{
  int i=0;
  int j=0;
  char buf[1024];
	int error;
  // cleat buffer
  for(i=0;i<1024;i++)
		buffer[i] = 0;
  // read data from gps
  error = read(fd,buffer, 1024);
  if(error > 0)
  {
    //cout << "error = " << error << endl << flush;
    //printf("buffer: %s\n",buffer);
    // look for start of sentence
    while(buffer[i] != 'G' && buffer[j] != 'P' && i<1024)
    {
      i++;
      j++;
    }
    //printf("offset = %d\n",i);
    if(i<1024)
    {
      strcpy(buf+1,buffer+i);
      buf[0] = '$';
      //printf("new avant cpy : %s\n",buf);
      strcpy(buffer,buf);
    }
    // look for end of sentence
    i = 0;
    while(buffer[i] != '\n')
      i++;
    // clear all after end of sentence
    for(;i<1024;i++)
      buffer[i] = 0;
    //printf("new buffer :%s\n",buffer);
  }
}

void Gps::updatePos()
{
    	readLineFromGps();
    	switch (minmea_sentence_id(buffer, false))
    {
      case MINMEA_SENTENCE_GGA:
      {
          //printf("GGA\n");
        if (minmea_parse_gga(&frame_gga, buffer))
        {
           longitude = (double)(frame_gga.longitude.value);
           degre = floor(longitude/1000000.0);
           minute = floor((longitude-degre*1000000.0)/10000.0);
           second = floor((longitude - degre*1000000.0 - minute*10000.0))/100.0;
           longitude = degre+minute/60.0+second/3600.0;
            //printf(" long : %f = %f + %f + %f\n",longitude,degre,minute/60.0,second/3600.0);
//		cout << "long : "<< degre << "°  "<< minute<< "'  " << second << "''  "<< endl;
           latitude = (double)(frame_gga.latitude.value);
           degre = floor(latitude/1000000.0);
           minute = floor((latitude-degre*1000000.0)/10000.0);
           second = floor((latitude - degre*1000000.0 - minute*10000.0))/100.0;
           latitude = degre+minute/60.0+second/3600.0;
            //printf(" lat : %f = %f + %f + %f\n",latitude,degre,minute/60.0,second/3600.0);
//	cout << "lat : "<< degre << "° " << minute<< "' "<< second << "'' "<< endl;
            //cout << " long now : "<< (float)longitude << endl;
            //cout << " lat now : " << (float)latitude << endl;
           if(m_mediator->getModeGps() == 1)
           {
             if(Gps::DirectDistance(m_mediator->getLatitude(),m_mediator->getLongitude(), latitude, longitude) < 1.0)
           	 {
               m_mediator->addLatitude(latitude);
               m_mediator->addLongitude(longitude);
             }
           }
           else
           {
             m_mediator->addLatitude(latitude);
             m_mediator->addLongitude(longitude);
           }
         }
         else
         {
           //printf(INDENT_SPACES "$xxGGA sentence is not parsed\n");
         }
      } break;

      case MINMEA_SENTENCE_RMC:
      {
          //printf("RMC\n");
	      if (minmea_parse_rmc(&frame_rmc, buffer))
        {
	         longitude = (double)(frame_rmc.longitude.value);
           degre = floor(longitude/1000000.0);
           minute = floor((longitude-degre*1000000.0)/10000.0);
           second = floor((longitude - degre*1000000.0 - minute*10000.0))/100.0;
           longitude = degre+minute/60.0+second/3600.0;
            //printf(" long : %f = %f + %f + %f\n",longitude,degre,minute/60.0,second/3600.0);
//		cout << "long : "<< degre << "°  "<< minute<< "'  " << second << "''  "<< endl;
           
           latitude = (double)(frame_rmc.latitude.value);
           degre = floor(latitude/1000000.0);
           minute = floor((latitude-degre*1000000.0)/10000.0);
           second = floor((latitude - degre*1000000.0 - minute*10000.0))/100.0;
           latitude = degre+minute/60.0+second/3600.0;
            //printf(" lat : %f = %f + %f + %f\n",latitude,degre,minute/60.0,second/3600.0);
//		cout << "lat : "<< degre << "° " << minute<< "' "<< second << "'' "<< endl;
        
            //cout << " long now : "<< (float)longitude << endl;
            //cout << " lat now : " << (float)latitude << endl;
	
           if(m_mediator->getModeGps() == 1)
           {
             if(Gps::DirectDistance(m_mediator->getLatitude(),m_mediator->getLongitude(), latitude, longitude) < 1.0)
           	 {
               m_mediator->addLatitude(latitude);
               m_mediator->addLongitude(longitude);
             }
           }
           else
           {
             m_mediator->addLatitude(latitude);
             m_mediator->addLongitude(longitude);
           }
         }
         else
         {
           //cout << "$xxRMC sentence is not parsed" << endl;
         }
       } break;

      case MINMEA_INVALID:
      {
        //cout << "$xxxxx sentence is not valid" << endl;
      } break;

      default:
      {
        //cout << "$xxxxx sentence is not parsed" << endl;
      } break;
    }
}

double Gps::getLong(void)
{
	return(longitude);
}

double Gps::getLat(void)
{
	return(latitude);
}


double Gps::ToRadians(double degrees)
{
	double radians = degrees*3.1415926535897932385/180.0;
	return radians;
}

// Distance between two points (longitude, latitude)
double Gps::DirectDistance(double lat1, double lng1, double lat2, double lng2)
{
	double earthRadius = 6371000; //meters
	double dLat = Gps::ToRadians(lat2-lat1);
	double dLng = Gps::ToRadians(lng2-lng1);
	double a = sin(dLat/2) * sin(dLat/2) +
	cos(Gps::ToRadians(lat1)) * cos(Gps::ToRadians(lat2)) *
	sin(dLng/2) * sin(dLng/2);
	double c = 2 * atan2(sqrt(a), sqrt(1-a));
	float dist = (float) (earthRadius * c);
	return dist;
}
