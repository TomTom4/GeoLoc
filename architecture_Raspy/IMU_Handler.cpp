#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <thread>
#include <pthread.h>
#include <mutex>
#include <assert.h>

#include "Model.h"
#include "const.hpp"
#include "Mediator.h"
#include "Spi.h"

using namespace std;

IMU *Imu::s_instance = 0;

IMU* Imu::instance()
{
	if(!Imu::s_instance)
		Imu::s_instance = new Imu();
		Imu::s_instance->m_mediator = Mediator::instance();
	return Imu::s_instance;
}

	Imu::Imu()
	{ // Constructor

		//** Create Thread
		result_code = pthread_create(&th_spi,NULL,thImuHelper,this);
	  if(result_code == 0)
	  cout << "Creation Thread IMU - Ok" << endl;
	}

	void* Imu::thImu(void)
	{
		while(1)
		{
			usleep(100000);
			Imu::readHeading();

		}
	}

	void *Imu::thImuHelper(void* context)
	{
	  return((Imu*)context)->Imu::thImu();
	}
