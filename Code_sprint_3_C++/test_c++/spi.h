#ifndef SPI_H
#define SPI_H

class Spi
{
  public:
  Spi(Car* voit);
  void readWriteData();
  void clearString();
  void addDataString();
  void extractUsSensor(int offset_string);
  void extractDataString();
  void majCar();

  protected:
  unsigned char lenght_string;
  unsigned char* string_spi;
  unsigned char beacon_rasp_start; // 0110b & 1001b
  unsigned char beacon_rasp_end; // 1010b & 0101b
  unsigned char beacon_stm_start; // 0011b & 1100b
  unsigned char beacon_stm_end; // 1110b & 0001b
  Car* voiture;

};

/* chaine spi :

      0 - beacon_start (rasp ou stm)
      1 - PWM Moteur AR G
      2 - PWM Moteur AR D
      3 - Compteur Direction
      4 - encodeur wheel AR G
      5 - encodeur wheel AR D

      6 - ID capteur US AV D
      7 - validité meusure US AV D
      8 - distance (cm) US AV D
      9 - ID capteur US AV C
     10 - validité meusure US AV C
     11 - distance (cm) US AV C
     12 - ID capteur US AV G
     13 - validité meusure US AV G
     14 - distance (cm) US AV G

     15 - ID capteur US AR D
     16 - validité meusure US AR D
     17 - distance (cm) US AR D
     18 - ID capteur US AR C
     19 - validité meusure US AR C
     20 - distance (cm) US AR C
     21 - ID capteur US AR G
     22 - validité meusure US AR G
     23 - distance (cm) US AR G

     24 - beacon_stop (rasp ou stm)
  */

#endif
