#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <pthread.h>
#include <assert.h>

#include "Model.h"
#include "const.hpp"
#include "Mediator.h"
#include "Spi.h"

using namespace std;


Spi *Spi::s_instance = 0;

	//Add your methodes over here
	Spi* Spi::instance(){
		if(!Spi::s_instance)
			Spi::s_instance = new Spi();
			Spi::s_instance->m_mediator = Mediator::instance();
		return Spi::s_instance;
	}

	Spi::Spi()
	{ // Constructor
		lenght_string = SPI_LENGHT_STRING;
		string_spi = new unsigned char[lenght_string];
		m_mediator = Mediator::instance();
		//** Create Thread
		result_code = pthread_create(&th_spi,NULL,thSpiHelper,this);
		if(result_code == 0)
			cout << "Thread Spi Ok" << endl;
	}

	void *Spi::thSpi(void)
	{
		while(1)
		{
			usleep(100000);
			Spi::majCar();
			cout << " Th SPI " << endl;
		}
	}

	void *Spi::thSpiHelper(void* context)
	{
		return((Spi*)context)->Spi::thSpi();
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
		cout << "avant get pwm" << endl;
		string_spi[PWM_MOTOR_BACK] = m_mediator->getPwmMotorBack(); // 1 - PWM Moteur AR
		cout << "avant get state" << endl;
		//string_spi[STATE_STEERING_WHEEL] = m_mediator->getStateSteeringWheel(); // 2 - Compteur Direction
		string_spi[3] = BEACON_RASP_END; // 3 - beacon_stop (rasp)
	}

	void Spi::extractDataString()
	{
		//try
		//{
			if(string_spi[BEACON_START] == BEACON_STM_START) // 0 - beacon_start (stm)
			{
				//if(m_mediator->getPwmMotorBack() != string_spi[PWM_MOTOR_BACK ]) // 1 - PWM Moteur AR
				//	throw string("ERREUR: PWM Motor AR D different");//	RASP:" << m_mediator->pwm_motor_ar_d << " STM:" << string_spi[1]);
				//if(m_mediator->getStateSteeringWheel() != string_spi[STATE_STEERING_WHEEL]) // 3 - State Direction
				//	throw string("ERREUR: Dir wrong position");//	RASP:" << m_mediator->cpt_dir << " STM:" << string_spi[3]);

				Spi::extractEncoder();
				m_mediator->addDistance((m_mediator->getEncoderWheelBackLeft()+m_mediator->getEncoderWheelBackRight())/2.0);
				m_mediator->addValidityFrontLeft(string_spi[US_VALIDITY_FRONT_LEFT]);
				m_mediator->addDistanceFrontLeft(string_spi[US_DISTANCE_FRONT_LEFT]);
				m_mediator->addValidityFrontCenter(string_spi[US_VALIDITY_FRONT_CENTER]);
				m_mediator->addDistanceFrontCenter(string_spi[US_DISTANCE_FRONT_CENTER]);
				m_mediator->addValidityFrontRight(string_spi[US_VALIDITY_FRONT_RIGHT]);
				m_mediator->addDistanceFrontRight(string_spi[US_DISTANCE_FRONT_RIGHT]);

				m_mediator->addValidityBackLeft(string_spi[US_VALIDITY_BACK_LEFT]);
				m_mediator->addDistanceBackLeft(string_spi[US_DISTANCE_BACK_LEFT]);
				m_mediator->addValidityBackCenter(string_spi[US_VALIDITY_BACK_CENTER]);
				m_mediator->addDistanceBackCenter(string_spi[US_DISTANCE_BACK_CENTER]);
				m_mediator->addValidityBackRight(string_spi[US_VALIDITY_BACK_RIGHT]);
				m_mediator->addDistanceBackRight(string_spi[US_DISTANCE_BACK_RIGHT]);
				
				//if(BEACON_STM_END != string_spi[BEACON_STOP]) // - beacon_end (stm)
				//	throw string("ERROR: Wrong beacon_stm_end");//	RASP:" << beacon_stm_start << " STM:" << string_spi[24]);

			}
			//else
			//	throw string("ERROR: Wrong beacon_stm_start");//	RASP:" << beacon_stm_start << " STM:" << string_spi[0]);
		//}
		//catch(string const& error_string)
		//{
			//cerr << error_string << endl;
		//}
	}

	void Spi::extractEncoder()
	{ // Calculate distance from left and right wheels
		// Add it to encoder_wheel_back_left && encoder_wheel_back_left in CAR structure
		unsigned char cpt_100m;
		unsigned char cpt_1m;
		unsigned char cpt_1cm;
		float dist;

		cpt_100m = string_spi[ENCODEUR_WHEEL_BACK_LEFT_100M];
		cpt_1m = string_spi[ENCODEUR_WHEEL_BACK_LEFT_1M];
		cpt_1cm = string_spi[ENCODEUR_WHEEL_BACK_LEFT_1CM];

		dist = (float)(cpt_100m)*100.0 + (float)(cpt_1m)*1.0 + (float)(cpt_1cm)*0.01;
		m_mediator->addEncoderWheelBackLeft(dist);
			cout << "Left " << (float)cpt_100m <<"/"<< (float)cpt_1m <<"/"<< (float)cpt_1cm<< " = "<<m_mediator->getEncoderWheelBackLeft()<< endl;

		cpt_100m = string_spi[ENCODEUR_WHEEL_BACK_RIGHT_100M];
		cpt_1m = string_spi[ENCODEUR_WHEEL_BACK_RIGHT_1M];
		cpt_1cm = string_spi[ENCODEUR_WHEEL_BACK_RIGHT_1CM];
		dist = (float)(cpt_100m)*100.0 + (float)(cpt_1m)*1.0 + (float)(cpt_1cm)*0.01;
		m_mediator->addEncoderWheelBackRight(dist);
			cout << "Left " << (float)cpt_100m <<"/"<< (float)cpt_1m <<"/"<< (float)cpt_1cm<< " = "<<m_mediator->getEncoderWheelBackRight()<< endl;

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
