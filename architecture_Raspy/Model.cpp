#include "Model.h"

using namespace std;
	//Add your methodes over here 
	Model::Model(){
		m_pwm_back_right_motor = 0;
		m_pwm_back_left_motor = 0;
		m_directional_counter = 0;
		m_back_right_wheel_encoder = 0;
		m_back_left_wheel_encoder = 0;

		m_right_front_ultrasonic_id = 0;
		m_right_front_ultrasonic_validity = 0;
		m_right_front_ultrasonic_distance = 0;

		m_center_front_ultrasonic_id = 0;
		m_center_front_ultrasonic_validity = 0;
		m_center_front_ultrasonic_distance = 0;

		m_left_front_ultrasonic_id = 0;
		m_left_front_ultrasonic_validity = 0;
		m_left_front_ultrasonic_distance = 0;

		m_right_back_ultrasonic_id = 0;
		m_right_back_ultrasonic_validity = 0;
		m_right_back_ultrasonic_distance = 0;

		m_center_back_ultrasonic_id = 0;
		m_center_back_ultrasonic_validity = 0;
		m_center_back_ultrasonic_distance = 0;

		m_left_back_ultrasonic_id = 0;
		m_left_back_ultrasonic_validity = 0;
		m_left_back_ultrasonic_distance = 0;
	}
	//getter for propulsors pwm
	unsigned char Model::getBackRightPwmMotor(){
		return Model::m_pwm_back_right_motor;
	}

	unsigned char Model::getBackLeftPwmMotor(){
		return Model::m_pwm_back_left_motor;
	}
	//getter for directional counter
	unsigned char Model::getDirectionalCounter(){
		return Model::m_directional_counter;
	}
	//getter for wheel Encoder
	unsigned char Model::getBackRightEncoderWheel(){
		return Model::m_back_right_wheel_encoder;
	}
	
	unsigned char Model::getBackLeftEncoderWheel(){
		return Model::m_back_left_wheel_encoder;
	}
	//getter for ultrasonic sensors
	unsigned char Model::getRightFrontUltrasonicId(){
		return Model::m_right_front_ultrasonic_id;
	}

	unsigned char Model::getRightFrontUltrasonicValidity(){
		return Model::m_right_front_ultrasonic_validity;
	}

	unsigned char Model::getRightFrontUltrasonicDistance(){
		return Model::m_right_front_ultrasonic_distance;
	}
	
	unsigned char Model::getCenterFrontUltrasonicId(){
		return Model::m_center_front_ultrasonic_id;
	}

	unsigned char Model::getCenterFrontUltrasonicValidity(){
		return Model::m_center_front_ultrasonic_validity;
	}

	unsigned char Model::getCenterFrontUltrasonicDistance(){
		return Model::m_center_front_ultrasonic_distance;
	}

	unsigned char Model::getLeftFrontUltrasonicId(){
		return Model::m_left_front_ultrasonic_id;
	}

	unsigned char Model::getLeftFrontUltrasonicValidity(){
		return Model::m_left_front_ultrasonic_validity;
	}

	unsigned char Model::getLeftFrontUltrasonicDistance(){
		return Model::m_left_front_ultrasonic_distance;
	}
	
	unsigned char Model::getBackRightUltrasonicId(){
		return Model::m_right_back_ultrasonic_id;
	}

	unsigned char Model::getBackRightUltrasonicValidity(){
		return Model::m_right_back_ultrasonic_validity;
	}

	unsigned char Model::getBackRightUltrasonicDistance(){
		return Model::m_right_back_ultrasonic_distance;
	}

	unsigned char Model::getBackCenterUltrasonicId(){
		return Model::m_center_back_ultrasonic_id;
	}

	unsigned char Model::getBackCenterUltrasonicValidity(){
		return Model::m_center_back_ultrasonic_validity;
	}

	unsigned char Model::getBackCenterUltrasonicDistance(){
		return Model::m_center_back_ultrasonic_distance;
	}

	unsigned char Model::getBackLeftUltrasonicId(){
		return Model::m_left_back_ultrasonic_id;
	}

	unsigned char Model::getBackLeftUltrasonicValidity(){
		return Model::m_left_back_ultrasonic_validity;
	}

	unsigned char Model::getBackLeftUltrasonicDistance(){
		return Model::m_left_back_ultrasonic_distance;
	}

