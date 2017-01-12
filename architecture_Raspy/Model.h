#ifndef DEF_MODEL
#define DEF_MODEL

#include <stdio.h>
#include <iostream>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "const.hpp"

class Model
{
	//private:
	public:
		Model(); // Constructor
		//~Model(); // Destructor

		//******** GET ********//
		//** PWM
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

	private:

		unsigned char pwm_motor_back;
		unsigned char state_steering_wheel;

		/*unsigned char encoder_wheel_back_left_100m;
		unsigned char encoder_wheel_back_left_1m;
		unsigned char encoder_wheel_back_left_1cm;
		unsigned char encoder_wheel_back_right_100m;
		unsigned char encoder_wheel_back_right_1m;
		unsigned char encoder_wheel_back_right_1cm;*/
	
		float encoder_wheel_back_left;
		float encoder_wheel_back_right;

		unsigned char us_id_front_left;
		unsigned char us_validity_front_left;
		unsigned char us_distance_front_left;

		unsigned char us_id_front_center;
		unsigned char us_validity_front_center;
		unsigned char us_distance_front_center;

		unsigned char us_id_front_right;
		unsigned char us_validity_front_right;
		unsigned char us_distance_front_right;

		unsigned char us_id_back_left;
		unsigned char us_validity_back_left;
		unsigned char us_distance_back_left;

		unsigned char us_id_back_center;
		unsigned char us_validity_back_center;
		unsigned char us_distance_back_center;

		unsigned char us_id_back_right;
		unsigned char us_validity_back_right;
		unsigned char us_distance_back_right;
};

#endif
