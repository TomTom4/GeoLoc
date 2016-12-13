#ifndef _GPS_H
#define _GPS_H

class Gps
{
  private:
    double longitude;
    double latitude;
    int nb_satellites;
    struct minmea_sentence_gga frame_gga;
    struct minmea_sentence_rmc frame_rmc;
    char* buffer; // Trame GPS
    int fd;
  public:
    Gps();
    void readLineFromGps();
    void getPos();
};

#endif
