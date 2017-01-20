#ifndef DEF_IMU_HANDLER
#define DEF_IMU_HANDLER

#include <thread>
#include <pthread.h>

#include "Model.h"
#include "const.hpp"
#include "Mediator.h"

using namespace std;

class Imu /*:: public Singleton*/
{
public:
	//** SINGLETON
	static Imu* instance();
	//** METHODS
	void readHeading(void);
	//** THREAD
	void* thImu(void);
	static void* thImuHelper(void* context);

private:
	//** SINGLETON
	Imu();
	Mediator *m_mediator;
	static Imu *s_instance;

	//** ATTRIBUTES


	//** ERROR
	int result_code;
	//** THREAD
	pthread_t th_imu;
};

#endif
