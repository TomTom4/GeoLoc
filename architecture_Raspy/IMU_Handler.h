#ifndef DEF_IMU_HANDLER
#define DEF_IMU_HANDLER

#include <thread>
#include <pthread.h>	
#include <string>

#include "Model.h"
#include "const.hpp"
#include "Mediator.h"

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>

#define PORT 5555
#define HOST NULL



using namespace std;

class Imu /*:: public Singleton*/
{
public:
	//** SINGLETON
	static Imu* instance();
	//** METHODS
	void readHeading();
	int socketInit();
	string readMessage(int sockfd);
	void ParseMessage( string message);
	//** THREAD
	void* thImu(void);
	static void* thImuHelper(void* context);

private:
	//** SINGLETON
	Imu();
	Mediator *m_mediator;
	static Imu *s_instance;
	string m_message;
	int m_magnetic;
	int m_cap;
	char m_buffer[8192];

	//** ATTRIBUTES

	//** ERROR
	int result_code;
	//** THREAD
	pthread_t th_imu;
};

#endif
