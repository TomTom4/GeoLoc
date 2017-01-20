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
#include "Imu_Handler.h"

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
{
// Constructor

	//** Create Thread
	result_code = pthread_create(&th_spi,NULL,thImuHelper,this);
	if(result_code == 0)
  		cout << "Creation Thread IMU - Ok" << endl;
}

void* Imu::thImu(void)
{

	while(1){

			//Imu::ComputeAverage();
			usleep(100000);
			Imu::readHeading();
	}
}

void *Imu::thImuHelper(void* context)
{
	return((Imu*)context)->Imu::thImu();
}

void Imu::readHeading(void)
{
}

string Imu::readMessage(int sockfd)
{
	bzero(buffer,8192);
	RWcharNumber = read(sockFileDescriptor, buffer, 8191);
	if( RWcharNumber < 0 )
		cout << "we are in PLS...." << endl;
	else
		cout << "this is the fucking message :" << buffer << endl ;
	string str(buffer);

}



int socketInit(){
	int sockFileDescriptor, RWcharNumber;
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
void ParseMessage(){
	string message;
	message = str(m_buffer);

}


void setHeadingImu(){
	if(m_magnetic < 50 )
		m_mediator.addHeadingImu(m_cap);
}
