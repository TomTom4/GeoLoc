#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <stdlib.h>

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
	cout << " aller on va chercher les données de l'IMU" << endl;


	while(1){

		Imu::ComputeAverage(sockfd);

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
	//cout <<"Message Imu : "<< MessageImu << endl;
	string buff("");
	string m [3] ;
	float magneNorm = 0;
	int repere =  MessageImu.find(" 5,");
	// cout << " allez vient on parse " << endl;
	if (repere != -1)
	{
		MessageImu = MessageImu.erase (0, repere+4);
		for (int i = 0; i<3; i++)
		{
	 		int j = 0;
			while ((MessageImu[j] != ',') && (j < MessageImu.size()))
			{
				buff+=MessageImu[j];
				j++;
			}
			if(buff != "")
			{
				m[i]=buff;
				buff = "";
			}
			MessageImu = MessageImu.erase(0, j+1);
		}
		double result[3];
		for (int x =0; x<3; x++)
		{
			result[x] = atof(m[x].c_str());
			magneNorm += result[x]*result[x];
			//	cout << "m[" << x << "] : "<< result [x] << endl;
		}
		Imu::m_magnetic = sqrt(magneNorm);
		Imu::m_cap = ((atan2(result[1],result[0])/M_PI)*180.0)-90.0;
		if (Imu::m_cap < -180.0) Imu::m_cap += 360.0;
		 	//cout << "Cap : " << Imu::m_cap << endl;
	}
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

void Imu::ComputeAverage(int sockfd)
{
	float headingAve= 0;
	for (int i =0; i<20; i++)
	{
		//cout << "th IMU" << endl;
		Imu::readMessage(sockfd);
		Imu::parseMessage();
		headingAve += Imu::m_cap;
		usleep(10000);
	}
	headingAve = headingAve /20;
	Imu::setHeadingImu();
}
