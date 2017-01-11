#ifndef DEF_MODEL
#define DEF_MODEL

class Model{

	public:
	//methodes
		Model();
	//getter for propulsors pwm
		unsigned char getBackPwmMotor();

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

	//setter for propulsors pwm
		void setBackPwmMotor(unsigned char value);

	//setter for directional counter
		void setDirectionalCounter(unsigned char value);

	//setter for wheel Encoder
		void setBackRightEncoderWheel(unsigned char value);
		void setBackLeftEncoderWheel(unsigned char value);
	//setters for ultrasonic sensors
		void setRightFrontUltrasonicId(unsigned char value);
		void setRightFrontUltrasonicValidity(unsigned char value);
		void setRightFrontUltrasonicDistance(unsigned char value);

		void setCenterFrontUltrasonicId(unsigned char value);
		void setCenterFrontUltrasonicValidity(unsigned char value);
		void setCenterFrontUltrasonicDistance(unsigned char value);

		void setLeftFrontUltrasonicId(unsigned char value);
		void setLeftFrontUltrasonicValidity(unsigned char value);
		void setLeftFrontUltrasonicDistance(unsigned char value);

		void setBackRightUltrasonicId(unsigned char value);
		void setBackRightUltrasonicValidity(unsigned char value);
		void setBackRightUltrasonicDistance(unsigned char value);

		void setBackCenterUltrasonicId(unsigned char value);
		void setBackCenterUltrasonicValidity(unsigned char value);
		void setBackCenterUltrasonicDistance(unsigned char value);

		void setBackLeftUltrasonicId(unsigned char value);
		void setBackLeftUltrasonicValidity(unsigned char value);
		void setBackLeftUltrasonicDistance(unsigned char value);

		//code louis*********************************************
		unsigned char getData(int num);
		void addData(unsigned char num, unsigned char val);
		void addDataEncodeur();
		void printEncodeur(void);
		void printCar(void);
		//*******************************************************


	private:
	//attributs
		unsigned char m_pwm_back_motor;
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

		//attributs louis
		unsigned char pwm_motor_back;
		unsigned char state_steering_wheel;
		unsigned char encodeur_wheel_back_left_100m;
		unsigned char encodeur_wheel_back_left_1m;
		unsigned char encodeur_wheel_back_left_1cm;
		unsigned char encodeur_wheel_back_right_100m;
		unsigned char encodeur_wheel_back_right_1m;
		unsigned char encodeur_wheel_back_right_1cm;

		float encodeur_wheel_back_left;
		float encodeur_wheel_back_right;

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
