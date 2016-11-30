/*
 * Copyright © 2014 Kosma Moczek <kosma@cloudyourcar.com>
 * This program is free software. It comes without any warranty, to the extent
 * permitted by applicable law. You can redistribute it and/or modify it under
 * the terms of the Do What The Fuck You Want To Public License, Version 2, as
 * published by Sam Hocevar. See the COPYING file for more details.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "minmea.h"

#define INDENT_SPACES "  "

int main(int argc, char* argv[])
{

   
    int i;    
    char * buffer = NULL;
    FILE * input_fd;
    size_t len = 0;
    ssize_t read;
    char line[1024];
     
    if(argc != 2){
        printf ("Usage: ./a.out gpsdata.log \n");
        return 1;
    }
    input_fd = fopen(argv [1], "r");


    while (fgets(line, sizeof(line), input_fd)) {
        //printf("GPS_READ_FILE:  line of length %d :\n", sizeof(line));
        //printf("GPS_READ_FILE: %s\n", line);
        GPS_parser(line);
    }
    fclose(input_fd);
    return 1;
}

int GPS_parser(char *buffer)
{

    int i;
    //while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        printf("GPS_PARSER: %s", buffer);
        switch (minmea_sentence_id(buffer, false)) {
            case MINMEA_SENTENCE_RMC: {
                struct minmea_sentence_rmc frame;
                if (minmea_parse_rmc(&frame, buffer)) {
                    printf(INDENT_SPACES "$xxRMC: raw coordinates and speed: (%d/%d,%d/%d) %d/%d\n",
                            frame.latitude.value, frame.latitude.scale,
                            frame.longitude.value, frame.longitude.scale,
                            frame.speed.value, frame.speed.scale);
                    printf(INDENT_SPACES "$xxRMC fixed-point coordinates and speed scaled to three decimal places: (%d,%d) %d\n",
                            minmea_rescale(&frame.latitude, 1000),
                            minmea_rescale(&frame.longitude, 1000),
                            minmea_rescale(&frame.speed, 1000));
                    printf(INDENT_SPACES "$xxRMC floating point degree coordinates and speed: (%f,%f) %f\n",
                            minmea_tocoord(&frame.latitude),
                            minmea_tocoord(&frame.longitude),
                            minmea_tofloat(&frame.speed));
                }
                else {
                    printf(INDENT_SPACES "$xxRMC sentence is not parsed\n");
                }
            } break;

            case MINMEA_SENTENCE_GGA: {
                struct minmea_sentence_gga frame;
                if (minmea_parse_gga(&frame, buffer)) {
                    printf(INDENT_SPACES "$xxGGA: fix quality: %d\n", frame.fix_quality);
                }
                else {
                    printf(INDENT_SPACES "$xxGGA sentence is not parsed\n");
                }
            } break;

            case MINMEA_SENTENCE_GST: {
                struct minmea_sentence_gst frame;
                if (minmea_parse_gst(&frame, buffer)) {
                    printf(INDENT_SPACES "$xxGST: raw latitude,longitude and altitude error deviation: (%d/%d,%d/%d,%d/%d)\n",
                            frame.latitude_error_deviation.value, frame.latitude_error_deviation.scale,
                            frame.longitude_error_deviation.value, frame.longitude_error_deviation.scale,
                            frame.altitude_error_deviation.value, frame.altitude_error_deviation.scale);
                    printf(INDENT_SPACES "$xxGST fixed point latitude,longitude and altitude error deviation"
                           " scaled to one decimal place: (%d,%d,%d)\n",
                            minmea_rescale(&frame.latitude_error_deviation, 10),
                            minmea_rescale(&frame.longitude_error_deviation, 10),
                            minmea_rescale(&frame.altitude_error_deviation, 10));
                    printf(INDENT_SPACES "$xxGST floating point degree latitude, longitude and altitude error deviation: (%f,%f,%f)",
                            minmea_tofloat(&frame.latitude_error_deviation),
                            minmea_tofloat(&frame.longitude_error_deviation),
                            minmea_tofloat(&frame.altitude_error_deviation));
                }
                else {
                    printf(INDENT_SPACES "$xxGST sentence is not parsed\n");
                }
            } break;

            case MINMEA_SENTENCE_GSV: {
                struct minmea_sentence_gsv frame;
                if (minmea_parse_gsv(&frame, buffer)) {
                    printf(INDENT_SPACES "$xxGSV: message %d of %d\n", frame.msg_nr, frame.total_msgs);
                    printf(INDENT_SPACES "$xxGSV: sattelites in view: %d\n", frame.total_sats);
                    for (i = 0; i < 4; i++)
                        printf(INDENT_SPACES "$xxGSV: sat nr %d, elevation: %d, azimuth: %d, snr: %d dbm\n",
                            frame.sats[i].nr,
                            frame.sats[i].elevation,
                            frame.sats[i].azimuth,
                            frame.sats[i].snr);
                }
                else {
                    printf(INDENT_SPACES "$xxGSV sentence is not parsed\n");
                }
            } break;

            case MINMEA_SENTENCE_VTG: {
               struct minmea_sentence_vtg frame;
               if (minmea_parse_vtg(&frame, buffer)) {
                    printf(INDENT_SPACES "$xxVTG: true track degrees = %f\n",
                           minmea_tofloat(&frame.true_track_degrees));
                    printf(INDENT_SPACES "        magnetic track degrees = %f\n",
                           minmea_tofloat(&frame.magnetic_track_degrees));
                    printf(INDENT_SPACES "        speed knots = %f\n",
                            minmea_tofloat(&frame.speed_knots));
                    printf(INDENT_SPACES "        speed kph = %f\n",
                            minmea_tofloat(&frame.speed_kph));
               }
               else {
                    printf(INDENT_SPACES "$xxVTG sentence is not parsed\n");
               }
            } break;

            case MINMEA_INVALID: {
                printf(INDENT_SPACES "$xxxxx sentence is not valid\n");
            } break;

            default: {
                printf(INDENT_SPACES "$xxxxx sentence is not parsed\n");
            } break;
        }
    //}
    
    return 0;
}

/* vim: set ts=4 sw=4 et: */
