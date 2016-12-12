#ifndef _GPS_H
#define _GPS_H

class Gps
{
private:
    double longitude;
    double latitude;
    double degre,minute,second;
    int nb_satellites;
    struct minmea_sentence_gga frame_gga;
    struct minmea_sentence_rmc frame_rmc;
    char buffer[1024]; // Trame GPS
    
    int fd;
public:
    Gps();
    void readLineFromGps();
    void updatePos();
    double getLong();
    double getLat();
};

#endif
