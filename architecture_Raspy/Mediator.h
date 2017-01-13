#ifndef DEF_MEDIATOR
#define DEF_MEDIATOR

#include "Model.h"
#include <pthread.h>

class Mediator{

	public:
		// singleton pattern methode
		static Mediator *instance();
		//all this method are extracted from model
		unsigned char getPwmMotorBack(void);
		//** Steering Wheel
		unsigned char getStateSteeringWheel(void);
		//** Encoder
		float getEncoderWheelBackLeft(void);
		float getEncoderWheelBackRight(void);
		//** US Validity
		unsigned char getValidityFrontLeft(void);
		unsigned char getValidityFrontCenter(void);
		unsigned char getValidityFrontRight(void);
		unsigned char getValidityBackLeft(void);
		unsigned char getValidityBackCenter(void);
		unsigned char getValidityBackRight(void);
		//** Distance
		unsigned char getDistanceFrontLeft(void);
		unsigned char getDistanceFrontCenter(void);
		unsigned char getDistanceFrontRight(void);
		unsigned char getDistanceBackLeft(void);
		unsigned char getDistanceBackCenter(void);
		unsigned char getDistanceBackRight(void);

		//** PWM
		void addPwmMotorBack(unsigned char val);

		//** Steering Wheel
		void addStateSteeringWheel(unsigned char val);

		//** Encoder
		void addEncoderWheelBackLeft(float val);
		void addEncoderWheelBackRight(float val);

		//** US Validity
		void addValidityFrontLeft(unsigned char val);
		void addValidityFrontCenter(unsigned char val);
		void addValidityFrontRight(unsigned char val);
		void addValidityBackLeft(unsigned char val);
		void addValidityBackCenter(unsigned char val);
		void addValidityBackRight(unsigned char val);
		void addDistanceFrontLeft(unsigned char val);
		void addDistanceFrontCenter(unsigned char val);
		void addDistanceFrontRight(unsigned char val);
		void addDistanceBackLeft(unsigned char val);
		void addDistanceBackCenter(unsigned char val);
		void addDistanceBackRight(unsigned char val);

		void printEncoder(void);
		void printModel(void);

		void Mediator::lockMutex(void);
		void Mediator::unlockMutex(void);

	private:
		Mediator();
		static Mediator *s_instance;
		Model m_model;
		pthread_mutex_t mutex_mediator;


};

#endif
