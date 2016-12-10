#include <iostream>
#include <stdio.h>
#include <string>

//#include <wiringPi.h>
//#include <wiringPiSPI.h>

#include "car.h"
#include "spi.h"

using namespace std;

  Spi::Spi(Car* voit)
  {
    lenght_string = 25;
    string_spi = new unsigned char[lenght_string];
    beacon_rasp_start = 0x69; // 0110b & 1001b
    beacon_rasp_end = 0xA5; // 1010b & 0101b
    beacon_stm_start = 0x3C; // 0011b & 1100b
    beacon_stm_end = 0xE1; // 1110b & 0001b
    voiture = voit;
  }

  void Spi::readWriteData()
  {
    //wiringPiSPIDataRW(0,string_spi,lenght_string);
  }

  void Spi::clearString()
  {
    for(int i = 0; i < lenght_string; i++)
      string_spi[i] = 0x00;
  }

  void Spi::addDataString()
  {
    clearString();
    string_spi[0] = beacon_rasp_start; // 0 - beacon_start (rasp)
    string_spi[1] = voiture->getData(1); // 1 - PWM Moteur AR G
    string_spi[2] = voiture->getData(2); // 2 - PWM Moteur AR D
    string_spi[3] = voiture->getData(3); // 3 - Compteur Direction
    string_spi[4] = beacon_rasp_end; // 4 - beacon_stop (rasp)
  }

  void Spi::extractUsSensor(int offset_string)
  { /* Check ID of US sensor from the stm
    if OK -> add validity & distance to Car structure */
    if(voiture->getData(offset_string) != string_spi[offset_string])
      throw string("ERREUR: US wrong ID");//  RASP:" << voiture->us_id_av_d << " STM:" << string_spi[6]);
    else
    {
      voiture->addData(offset_string+1, string_spi[offset_string+1]);
      voiture->addData(offset_string+2, string_spi[offset_string+2]);
    }
  }

  void Spi::extractDataString()
  {
    try
    {
      if(string_spi[0] == beacon_stm_start) // 0 - beacon_start (stm)
      {
        if(voiture->getData(1) != string_spi[1]) // 1 - PWM Moteur AR G
          throw string("ERREUR: PWM Motor AR D different");//  RASP:" << voiture->pwm_motor_ar_d << " STM:" << string_spi[1]);
        if(voiture->getData(2) != string_spi[2]) // 2 - PWM Moteur AR D
          throw string("ERREUR: PWM Motor AR G different");//  RASP:" << voiture->pwm_motor_ar_g << " STM:" << string_spi[2]);
        if(voiture->getData(3) != string_spi[3]) // 3 - Compteur Direction
          throw string("ERREUR: Dir wrong position");//  RASP:" << voiture->cpt_dir << " STM:" << string_spi[3]);

        /* Prise du mutex SPI */

        voiture->addData(4, string_spi[4]); // 4 - encodeur wheel AR G
        voiture->addData(5, string_spi[5]); // 5 - encodeur wheel AR D

        extractUsSensor(6); // 6 - ID capteur US AV D
        extractUsSensor(9); // 9 - ID capteur US AV C
        extractUsSensor(12); // 12 - ID capteur US AV G
        extractUsSensor(15); // 15 - ID capteur US AR D
        extractUsSensor(18); // 18 - ID capteur US AR C
        extractUsSensor(21); // 21 - ID capteur US AR G

        if(beacon_stm_end != string_spi[24]) // 24 - beacon_end (stm)
          throw string("ERROR: Wrong beacon_stm_end");//  RASP:" << beacon_stm_start << " STM:" << string_spi[24]);

        /* Restitution du mutex */
      }
      else
        throw string("ERROR: Wrong beacon_stm_start");//  RASP:" << beacon_stm_start << " STM:" << string_spi[0]);
    }
    catch(string const& error_string)
    {
      cerr << error_string << endl;
    }
  }

  void Spi::majCar()
  {
    addDataString();
    readWriteData();
    extractDataString();
  }
