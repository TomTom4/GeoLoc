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
#include "IMU_Handler.h"

using namespace std;

Imu *Imu::s_instance = 0;

Imu* Imu::instance()
{
	if(!Imu::s_instance)
		Imu::s_instance = new Imu();
	Imu::s_instance->m_mediator = Mediator::instance();
	return Imu::s_instance;
}

Imu::Imu()
{
// Constructor

		//** Create Thread
		result_code = pthread_create(&th_imu,NULL,thImuHelper,this);
	  if(result_code == 0)
	  cout << "Creation Thread IMU - Ok" << endl;
	}

void* Imu::thImu(void)
{
	int sockfd; 
	sockfd = socketInit();
	

	while(1){

		//Imu::ComputeAverage();
		usleep(100000);
		Imu::readMessage(sockfd);
		Imu::parseMessage();
			
	}
}

void *Imu::thImuHelper(void* context)
{
	return((Imu*)context)->Imu::thImu();
}

void Imu::readMessage(int sockfd)
{
	int RWcharNumber ;
	bzero(Imu::m_buffer,8192);
	RWcharNumber = read(sockfd, Imu::m_buffer, 8191);
	if( RWcharNumber < 0 )
		cout << "we are in PLS...." << endl;
}


void Imu::parseMessage(void)
{
	string MessageImu(Imu::m_buffer);
	int repere = MessageImu.find(" 5,");
	MessageImu = MessageImu.substr(0, repere);
	float m[] = MessageImu.split(',');
	Imu::m_cap = atan2(m[1],m[0])/pi)*180.0)
}

int Imu::socketInit(){
	int sockFileDescriptor;
	struct sockaddr_in server_addr;

	sockFileDescriptor = socket( AF_INET, SOCK_DGRAM, 0);
	if(sockFileDescriptor  == -1)
		cout << "You don't freaking work biatch !! "<<endl ;

	bzero((char *) &server_addr, sizeof(server_addr));// here it set server_addr in memory with zero values


	server_addr.sin_family = AF_INET;// should alway be that value
	server_addr.sin_port = htons(PORT);// very important to convert using htons
	server_addr.sin_addr.s_addr = INADDR_ANY;// this is a UDP Server, doesn't need to speak with anyone

	if(bind(sockFileDescriptor, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
		cout << "it doesn't bind you freaking basterd!!!!"<< endl;

	return sockFileDescriptor;
}


void Imu::setHeadingImu(){
	Imu::m_mediator->addHeadingImu(Imu::m_cap);
}