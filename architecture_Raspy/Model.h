#ifndef DEF_MODEL
#define DEF_MODEL

class Model{

	public:
	//methodes
		Model();
	//getter for propulsors pwm
		unsigned char getBackRightPwmMotor();
		unsigned char getBackLeftPwmMotor();

	//getter for directional counter
	unsigned char getDirectionalCounter();

	//getter for wheel Encoder
		unsigned char getBackRightEncoderWheel();
		unsigned char getBackLeftEncoderWheel();

	//getter for ultrasonic sensors
		unsigned char getRightFrontUltrasonicId();
		unsigned char getRightFrontUltrasonicValidity();
		unsigned char getRightFrontUltrasonicDistance();
		unsigned char getCenterFrontUltrasonicId();
		unsigned char getCenterFrontUltrasonicValidity();
		unsigned char getCenterFrontUltrasonicDistance();
		unsigned char getLeftFrontUltrasonicId();
		unsigned char getLeftFrontUltrasonicValidity();
		unsigned char getLeftFrontUltrasonicDistance();
		unsigned char getBackRightUltrasonicId();
		unsigned char getBackRightUltrasonicValidity();
		unsigned char getBackRightUltrasonicDistance();
		unsigned char getBackCenterUltrasonicId();
		unsigned char getBackCenterUltrasonicValidity();
		unsigned char getBackCenterUltrasonicDistance();
		unsigned char getBackLeftUltrasonicId();
		unsigned char getBackLeftUltrasonicValidity();
		unsigned char getBackLeftUltrasonicDistance();

	private:
	//attributs
		unsigned char m_pwm_back_right_motor;
		unsigned char m_pwm_back_left_motor;
		unsigned char m_directional_counter;
		unsigned char m_back_right_wheel_encoder;
		unsigned char m_back_left_wheel_encoder;

		unsigned char m_right_front_ultrasonic_id;
		unsigned char m_right_front_ultrasonic_validity;
		unsigned char m_right_front_ultrasonic_distance;

		unsigned char m_center_front_ultrasonic_id;
		unsigned char m_center_front_ultrasonic_validity;
		unsigned char m_center_front_ultrasonic_distance;

		unsigned char m_left_front_ultrasonic_id;
		unsigned char m_left_front_ultrasonic_validity;
		unsigned char m_left_front_ultrasonic_distance;

		unsigned char m_right_back_ultrasonic_id;
		unsigned char m_right_back_ultrasonic_validity;
		unsigned char m_right_back_ultrasonic_distance;

		unsigned char m_center_back_ultrasonic_id;
		unsigned char m_center_back_ultrasonic_validity;
		unsigned char m_center_back_ultrasonic_distance;

		unsigned char m_left_back_ultrasonic_id;
		unsigned char m_left_back_ultrasonic_validity;
		unsigned char m_left_back_ultrasonic_distance;


};

#endif
