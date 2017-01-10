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
	//int etat = -1;
	//while(etat != 0)
	//{
	wiringPiSPIDataRW(0,(unsigned char*)string_spi,lenght_string);
    	//printf(" chaine = %d\n",string_spi[0]);
	//printf(" taille = %d\n",lenght_string);
	//printf(" etat = %d\n",etat);
  	//}
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
    string_spi[PWM_MOTOR_BACK] = voiture->getData(PWM_MOTOR_BACK); // 1 - PWM Moteur AR
    string_spi[STATE_STEERING_WHEEL] = voiture->getData(STATE_STEERING_WHEEL); // 2 - Compteur Direction
    string_spi[3] = BEACON_RASP_END; // 3 - beacon_stop (rasp)
  }

  void Spi::extractUsSensor(int offset_string)
  { /* Check ID of US sensor from the stm
    if OK -> add validity & distance to Car structure */
    // offset_string = ID Position
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
      if(string_spi[BEACON_START] == BEACON_STM_START) // 0 - beacon_start (stm)
      {
        if(voiture->getData(PWM_MOTOR_BACK) != string_spi[PWM_MOTOR_BACK ]) // 1 - PWM Moteur AR
          throw string("ERREUR: PWM Motor AR D different");//  RASP:" << voiture->pwm_motor_ar_d << " STM:" << string_spi[1]);
        if(voiture->getData(STATE_STEERING_WHEEL) != string_spi[STATE_STEERING_WHEEL]) // 3 - State Direction
          throw string("ERREUR: Dir wrong position");//  RASP:" << voiture->cpt_dir << " STM:" << string_spi[3]);

        /* Prise du mutex SPI */

        Spi::extractEncodeur();
        extractUsSensor(US_ID_FRONT_LEFT); // - ID capteur US AV D
        extractUsSensor(US_ID_FRONT_CENTER); // - ID capteur US AV C
        extractUsSensor(US_ID_FRONT_RIGHT); // - ID capteur US AV G
        extractUsSensor(US_ID_BACK_LEFT); // - ID capteur US AR D
        extractUsSensor(US_ID_BACK_CENTER); // - ID capteur US AR C
        extractUsSensor(US_ID_BACK_RIGHT); // - ID capteur US AR G

        if(BEACON_STM_END != string_spi[BEACON_STOP]) // - beacon_end (stm)
          throw string("ERROR: Wrong beacon_stm_end");//  RASP:" << beacon_stm_start << " STM:" << string_spi[24]);

        /* Restitution du mutex */
      }
      else
        throw string("ERROR: Wrong beacon_stm_start");//  RASP:" << beacon_stm_start << " STM:" << string_spi[0]);
    }
    catch(string const& error_string)
    {
      //cerr << error_string << endl;
    }
  }

  void Spi::extractEncodeur()
  { // Calculate distance from left and right wheels
    // Add it to encodeur_wheel_back_left && encodeur_wheel_back_left in CAR structure
	//voiture->encodeur_wheel_back_left_100m = string_spi[3];
	//voiture->encodeur_wheel_back_left_1m = string_spi[4];
	//voiture->encodeur_wheel_back_left_1cm = string_spi[5];
    
	//cout << "100m = "<< (int)voiture->encodeur_wheel_back_left_100m << endl;
    /*voiture->addData(ENCODEUR_WHEEL_BACK_LEFT_100M, string_spi[ENCODEUR_WHEEL_BACK_LEFT_100M]);
    voiture->addData(ENCODEUR_WHEEL_BACK_LEFT_1M, string_spi[ENCODEUR_WHEEL_BACK_LEFT_1M]);
    voiture->addData(ENCODEUR_WHEEL_BACK_LEFT_1CM, string_spi[ENCODEUR_WHEEL_BACK_LEFT_1CM]);
    voiture->addData(ENCODEUR_WHEEL_BACK_RIGHT_100M, string_spi[ENCODEUR_WHEEL_BACK_RIGHT_100M]);
    voiture->addData(ENCODEUR_WHEEL_BACK_RIGHT_1M, string_spi[ENCODEUR_WHEEL_BACK_RIGHT_1M]);
    voiture->addData(ENCODEUR_WHEEL_BACK_RIGHT_1CM, string_spi[ENCODEUR_WHEEL_BACK_RIGHT_1CM]);*/
    //voiture->addDataEncodeur();
  }

  void Spi::majCar()
  {
    addDataString();
    //cout << "Tx :";
    //Spi::printStringSpi();
    readWriteData();
    //cout << "Rx :";
    Spi::printStringSpi();
    extractDataString();
  }

  void Spi::printStringSpi()
  {
	/*for(int i = 0; i< lenght_string; i++)
	  cout <<(int)string_spi[i]<<"|";
	cout << endl;*/
	printf("Distance Left = %02d%02d.%02dm \n",(int)string_spi[3],(int)string_spi[4],(int)string_spi[5]);
	printf("Distance Right = %02d%02d.%02dm \n",(int)string_spi[6],(int)string_spi[7],(int)string_spi[8]);
  }
