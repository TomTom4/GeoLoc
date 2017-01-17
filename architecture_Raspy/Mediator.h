#ifndef DEF_MEDIATOR
#define DEF_MEDIATOR

#include <mutex>
#include "Model.h"

using namespace std;
class Mediator{

	public:
		//** SINGLETON
		static Mediator *instance();
		//** METHODS

		//******** GET ********//
		//** PWM
		unsigned char getPwmMotorBack(void);
		//** Steering Wheel
		unsigned char getStateSteeringWheel(void);
		//** Encoder
		float getEncoderWheelBackLeft(void);
		float getEncoderWheelBackRight(void);
		float getDistance(void);
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
		//** Gps
		double getLongitude(void);
		double getLatitude(void);

		//******** ADD ********//
		//** PWM
		void addPwmMotorBack(unsigned char val);
		//** Steering Wheel
		void addStateSteeringWheel(unsigned char val);
		//** Encoder
		void addEncoderWheelBackLeft(float val);
		void addEncoderWheelBackRight(float val);
		void addDistance(float val);
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
		//** Gps
		void addLongitude(double val);
		void addLatitude(double val);

		//******** PRINT ********//
		void printEncoder(void);
		void printModel(void);
		//******** THREAD ********//
		void lockMutex(void);
		void unlockMutex(void);

	private:
		//** SINGLETON
		Mediator();
		Model m_model;
		static Mediator *s_instance;
		//** THREAD
		mutex* mutex_mediator;
};

#endif
