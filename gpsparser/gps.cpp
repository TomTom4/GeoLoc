#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "minmea.h"
#include "gps.h"
#define INDENT_SPACES "  "

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
    write(fd, "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28\r\n", 53);  //<CR><LF>
    usleep(50000);
  }

  /***************************READ_LINE_FROM_GPS********************************/
/* Get a line from GPS data flow in /dev/ttyUSB0 and returns it into a buffer*/
/* In : the file descriptor for /dev/ttyUSB0                                 */
/* In/Out: the char * buffer where the extracted line is written             */
/*****************************************************************************/

void Gps::readLineFromGps()
{
  char c;
  char *b = buffer;
  int length = -1;

  while(1)
  {
    // read current character
    length = read(fd, (void*)(&c), 1);
    // if read failed
    if(length <= 0)
    {
      for (int i = 0; i<100; i++)
        usleep(10);
    }
    else
    {
      // end of line
      if (c == '\n')
      {
        *b++ = '\0';
        break;
      }
      // middle of line
      else
        *b++ = c;
    }
  }
}

  void Gps::getPos()
  {
    readLineFromGps();
    switch (minmea_sentence_id(buffer, false))
    {
        case MINMEA_SENTENCE_GGA:
        {
            if (minmea_parse_gga(&frame_gga, buffer))
            {
              longitude = (double)frame_gga.longitude.value/(frame_gga.longitude.scale*100);
              latitude = (double)frame_gga.latitude.value/(frame_gga.latitude.scale*100);
              nb_satellites = frame_gga.satellites_tracked;
              printf(" long : %f\n",latitude);
              printf(" lat : %f\n",longitude);
              printf(" nb sat: %d\n",nb_satellites);
            }
            else
            {
                printf(INDENT_SPACES "$xxGGA sentence is not parsed\n");
            }
          } break;

          case MINMEA_SENTENCE_RMC:
          {
              if (minmea_parse_rmc(&frame_rmc, buffer))
              {
                longitude = (double)frame_rmc.longitude.value/(frame_rmc.longitude.scale*100);
                latitude = (double)frame_rmc.latitude.value/(frame_rmc.latitude.scale*100);
                printf(" long : %f\n",latitude);
                printf(" lat : %f\n",longitude);
              }
              else
              {
                  printf(INDENT_SPACES "$xxRMC sentence is not parsed\n");
              }
            } break;

          case MINMEA_INVALID: {
              printf(INDENT_SPACES "$xxxxx sentence is not valid\n");
          } break;

          default: {
              printf(INDENT_SPACES "$xxxxx sentence is not parsed\n");
          } break;
  }
}
