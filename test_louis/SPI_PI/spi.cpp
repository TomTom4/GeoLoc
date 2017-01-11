#include <iostream>
#include <stdio.h>
#include <string>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "car.hpp"
#include "spi.hpp"
#include "const.hpp"


using namespace std;

  Spi::Spi(Car* voit)
  { // Constructor
    lenght_string = SPI_LENGHT_STRING;
    string_spi = new unsigned char[lenght_string];
    voiture = voit;
  }

  void Spi::readWriteData()
  {
    wiringPiSPIDataRW(0,(unsigned char*)string_spi,lenght_string);
    //printf(" chaine = %d\n",string_spi[0]);
	  //printf(" taille = %d\n",lenght_string);
	  //printf(" etat = %d\n",etat);
}

  void Spi::clearString()
  {
    for(int i = 0; i < lenght_string; i++)
      string_spi[i] = 0x00;
  }

  void Spi::addDataString()
  { // Add data to send to STM 32
      // 1 - PWM Moteur AR
      // 2 - Compteur Direction

    clearString();
    string_spi[BEACON_START] = BEACON_RASP_START; // 0 - beacon_start (rasp)
    string_spi[PWM_MOTOR_BACK] = voiture->getPwmMotorBack(); // 1 - PWM Moteur AR
    string_spi[STATE_STEERING_WHEEL] = voiture->getStateSteeringWheel(); // 2 - Compteur Direction
    string_spi[3] = BEACON_RASP_END; // 3 - beacon_stop (rasp)
  }

  void Spi::extractDataString()
  {
    try
    {
      if(string_spi[BEACON_START] == BEACON_STM_START) // 0 - beacon_start (stm)
      {
        if(voiture->getData(PWM_MOTOR_BACK) != string_spi[PWM_MOTOR_BACK ]) // 1 - PWM Moteur AR
          throw string("ERREUR: PWM Motor AR D different");//  RASP:" << voiture->pwm_motor_ar_d << " STM:" << string_spi[1]);
        if(voiture->getData(STATE_STEERING_WHEEL) != string_spi[STATE_STEERING_WHEEL]) // 3 - State Direction
          throw string("ERREUR: Dir wrong position");//  RASP:" << voiture->cpt_dir << " STM:" << string_spi[3]);

        /* Prise du mutex SPI */
        Spi::extractEncodeur();
        voiture->addValidityFrontLeft(string_spi[US_VALIDITY_FRONT_LEFT]);
        voiture->addDistanceFrontLeft(string_spi[US_DISTANCE_FRONT_LEFT]);
        voiture->addValidityFrontCenter(string_spi[US_VALIDITY_FRONT_CENTER]);
        voiture->addDistanceFrontCenter(string_spi[US_DISTANCE_FRONT_CENTER]);
        voiture->addValidityFrontRight(string_spi[US_VALIDITY_FRONT_RIGHT]);
        voiture->addDistanceFrontRight(string_spi[US_DISTANCE_FRONT_RIGHT]);

        voiture->addValidityBackLeft(string_spi[US_VALIDITY_BACK_LEFT]);
        voiture->addDistanceBackLeft(string_spi[US_DISTANCE_BACK_LEFT]);
        voiture->addValidityBackCenter(string_spi[US_VALIDITY_BACK_CENTER]);
        voiture->addDistanceBackCenter(string_spi[US_DISTANCE_BACK_CENTER]);
        voiture->addValidityBackRight(string_spi[US_VALIDITY_BACK_RIGHT]);
        voiture->addDistanceBackRight(string_spi[US_DISTANCE_BACK_RIGHT]);

        if(BEACON_STM_END != string_spi[BEACON_STOP]) // - beacon_end (stm)
          throw string("ERROR: Wrong beacon_stm_end");//  RASP:" << beacon_stm_start << " STM:" << string_spi[24]);

        /* Restitution du mutex */
      }
      else
        throw string("ERROR: Wrong beacon_stm_start");//  RASP:" << beacon_stm_start << " STM:" << string_spi[0]);
    }
    catch(string const& error_string)
      //cerr << error_string << endl;
    }
  }

  void Spi::extractEncodeur()
  { // Calculate distance from left and right wheels
    // Add it to encodeur_wheel_back_left && encodeur_wheel_back_left in CAR structure
    unsigned char cpt_100m;
    unsigned char cpt_1m;
    unsigned char cpt_1cm;
    float dist;

    cpt_100m = string_spi[ENCODEUR_WHEEL_BACK_LEFT_100M];
    cpt_1m = string_spi[ENCODEUR_WHEEL_BACK_LEFT_1M];
    cpt_1cm = string_spi[ENCODEUR_WHEEL_BACK_LEFT_1CM];

    dist = (float)(cpt_100m)*100.0 + (float)(cpt_1m)*1.0 + (float)(cpt_1cm)*0.01;
    voiture->encodeur_wheel_back_left = dist;
      cout << "Left " << (float)cpt_100m <<"/"<< (float)cpt_1m <<"/"<< (float)cpt_1cm<< " = "<<voiture->encodeur_wheel_back_left<< endl;

    cpt_100m = string_spi[ENCODEUR_WHEEL_BACK_RIGHT_100M];
    cpt_1m = string_spi[ENCODEUR_WHEEL_BACK_RIGHT_1M];
    cpt_1cm = string_spi[ENCODEUR_WHEEL_BACK_RIGHT_1CM];
    dist = (float)(cpt_100m)*100.0 + (float)(cpt_1m)*1.0 + (float)(cpt_1cm)*0.01;
    voiture->encodeur_wheel_back_right = dist;
      cout << "Left " << (float)cpt_100m <<"/"<< (float)cpt_1m <<"/"<< (float)cpt_1cm<< " = "<<voiture->encodeur_wheel_back_left<< endl;

  }

  void Spi::majCar()
  {
    addDataString();
      cout << "Tx :";
      Spi::printStringSpi();
    readWriteData();
    extractDataString();
      cout << "Rx :";
      Spi::printStringSpi();
  }

  void Spi::printStringSpi()
  {
    for(int i = 0; i< lenght_string; i++)
	    cout <<(int)string_spi[i]<<"|";
	  cout << endl;
	}
