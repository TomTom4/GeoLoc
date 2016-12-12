#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cmath>

#include "minmea.h"
#include "gps.h"

#define INDENT_SPACES "  "

using namespace std;

//extern enum minmea_sentence_id minmea_sentence_id(const char *sentence, bool strict);
//extern bool minmea_parse_rmc(struct minmea_sentence_rmc *frame, const char *sentence);
//extern bool minmea_parse_gga(struct minmea_sentence_gga *frame, const char *sentence);


  Gps::Gps()
  {
    /********************************GPS_INIT*************************************/
    /* Opens the /dev/ttyUSB0 file where GPS data are written                    */
    /* Out : the file descriptor for /dev/ttyUSB0                                */
    /*****************************************************************************/
    longitude = 0;
    latitude = 0;
    nb_satellites = 0;
    fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)
    {
      printf("GPS_Driver.c -> GPS_init -> Error opening /dev/ttyUSB0");
      exit(1);
    }
    usleep(100000);

    // set baud_rate = 115200
    write(fd, "$PMTK251,115200*2C\r\n", 20);  //<CR><LF>
    usleep(50000);

    // set FIX update rate = 5Hz
    write(fd, "$PMTK220,200*0F\r\n", 20);
    usleep(100000);

    // enable RMC & GGA only (send every FIX update)
    write(fd, "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28\r\n", 52);  //<CR><LF>
    usleep(50000);
  }

  /***************************READ_LINE_FROM_GPS********************************/
/* Get a line from GPS data flow in /dev/ttyUSB0 and returns it into a buffer*/
/* In : the file descriptor for /dev/ttyUSB0                                 */
/* In/Out: the char * buffer where the extracted line is written             */
/*****************************************************************************/

void Gps::readLineFromGps()
{
  int i,j;
  char buf[1024];
  i = 0;
  j = 1;

  // cleat buufer
  for(i=0;i<1024;i++)
		buffer[i] = 0;
  // read data from gps
  read(fd,buffer, 1024);
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

  void Gps::updatePos()
  {
    bool ack = false;
    do
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
                //printf(" long : %f + %f + %f\n",degre,minute,second);
		longitude = degre+minute/60.0+second/3600.0;
                //printf(" long : %f = %f + %f + %f\n",longitude,degre,minute/60.0,second/3600.0);
                printf(" long : %f\n",longitude);

	      latitude = (double)(frame_gga.latitude.value);
              	degre = floor(latitude/1000000.0);
		minute = floor((latitude-degre*1000000.0)/10000.0);
		second = floor((latitude - degre*1000000.0 - minute*10000.0))/100.0;
                //printf(" lat : %f + %f + %f\n",degre,minute,second);
		latitude = degre+minute/60.0+second/3600.0;
                //printf(" lat : %f = %f + %f + %f\n",latitude,degre,minute/60.0,second/3600.0);
            	printf(" lat : %f\n",latitude);
		ack = true;
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
                //printf(" long : %f + %f + %f\n",degre,minute,second);
		longitude = degre+minute/60.0+second/3600.0;
                //printf(" long : %f = %f + %f + %f\n",longitude,degre,minute/60.0,second/3600.0);
        	printf(" long : %f\n",longitude);

		latitude = (double)(frame_rmc.latitude.value);
              	degre = floor(latitude/1000000.0);
		minute = floor((latitude-degre*1000000.0)/10000.0);
		second = floor((latitude - degre*1000000.0 - minute*10000.0))/100.0;
                //printf(" lat : %f + %f + %f\n",degre,minute,second);
		latitude = degre+minute/60.0+second/3600.0;
                //printf(" lat : %f = %f + %f + %f\n",latitude,degre,minute/60.0,second/3600.0);
	        printf(" lat : %f\n",latitude);
		ack = true;
		}
              else
              {
                  printf(INDENT_SPACES "$xxRMC sentence is not parsed\n");
              }
            } break;

          case MINMEA_INVALID: {
              //printf(INDENT_SPACES "$xxxxx sentence is not valid\n");
          } break;

          default: {
              //printf(INDENT_SPACES "$xxxxx sentence is not parsed\n");
          } break;
	}
     }while(ack == false);
}

double Gps::getLong(void)
{
	return(longitude);
}

double Gps::getLat(void)
{
	return(latitude);
}
