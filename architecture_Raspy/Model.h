#ifndef DEF_MODEL
#define DEF_MODEL

class Model
{
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
		int getModeGps(void);
		//** IMU
		int getHeadingImu();
		//** Music
		int getCptMusic(void);

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
		void addModeGps(int val);
		//** IMU
		void addHeadingImu(int headingImu);
		//** Music
		void addCptMusic(int val);

		//******** PRINT ********//
		void printEncoder(void);
		void printModel(void);
		void printGps(void);

	private:

		//** PWM
		unsigned char pwm_motor_back;
		//** Steering Wheel
		unsigned char state_steering_wheel;
		//** Encoder
		float encoder_wheel_back_left;
		float encoder_wheel_back_right;
		float distance;

		//** US Validity
		unsigned char us_validity_front_left;
		unsigned char us_validity_front_center;
		unsigned char us_validity_front_right;
		unsigned char us_validity_back_left;
		unsigned char us_validity_back_center;
		unsigned char us_validity_back_right;

		//** Distance
		unsigned char us_distance_front_left;
		unsigned char us_distance_front_center;
		unsigned char us_distance_front_right;
		unsigned char us_distance_back_left;
		unsigned char us_distance_back_center;
		unsigned char us_distance_back_right;

		//** Gps
		double longitude;
		double latitude;
		int mode_gps; // 0 = all datas from GPS are OK
									// 1 = Only datas at less than 1m compared to
									// the previous position are OK
		//** IMU
		int heading_imu;
						
		//** Music
		int cpt_music;

};

#endif
