
#include <stdio.h>
#include <iostream>

#include "Model.h"

using namespace std;

Model::Model()
{
  pwm_motor_back = 0;
  state_steering_wheel = 12;
  encoder_wheel_back_left = 0.0;
  encoder_wheel_back_right = 0.0;
  distance = 0.0;

  us_validity_front_left = 0;
  us_distance_front_left = 0xFF;

  us_validity_front_center = 0;
  us_distance_front_center = 0xFF;

  us_validity_front_right = 0;
  us_distance_front_right = 0xFF;

  us_validity_back_left = 0;
  us_distance_back_left = 0xFF;

  us_validity_back_center = 0;
  us_distance_back_center = 0xFF;

  us_validity_back_right = 0;
  us_distance_back_right = 0xFF;

  longitude = 0.0;
  latitude = 0.0;
  mode_gps = 0;

  heading_imu = 0.0;

  cpt_music = 0;
}

//******** GET ********//

//** PWM
unsigned char Model::getPwmMotorBack(void)
{
  //cout << " dans model pwm" << endl;
  return(pwm_motor_back);
}

//** Steering Wheel
unsigned char Model::getStateSteeringWheel(void)
{
  return(state_steering_wheel);
}

//** Encoder
float Model::getEncoderWheelBackLeft(void)
{
  return(encoder_wheel_back_left);
}
float Model::getEncoderWheelBackRight(void)
{
  return(encoder_wheel_back_right);
}
float Model::getDistance(void)
{
  return(distance);
}

//** US Validity
unsigned char Model::getValidityFrontLeft(void)
{
  return(us_validity_front_left);
}
unsigned char Model::getValidityFrontCenter(void)
{
  return(us_validity_front_center);
}
unsigned char Model::getValidityFrontRight(void)
{
  return(us_validity_front_right);
}
unsigned char Model::getValidityBackLeft(void)
{
  return(us_validity_back_left);
}
unsigned char Model::getValidityBackCenter(void)
{
  return(us_validity_back_center);
}
unsigned char Model::getValidityBackRight(void)
{
  return(us_validity_back_left);
}

//** Distance
unsigned char Model::getDistanceFrontLeft(void)
{
  return(us_distance_front_left);
}
unsigned char Model::getDistanceFrontCenter(void)
{
  return(us_distance_front_center);
}
unsigned char Model::getDistanceFrontRight(void)
{
  return(us_distance_front_right);
}
unsigned char Model::getDistanceBackLeft(void)
{
  return(us_distance_back_left);
}
unsigned char Model::getDistanceBackCenter(void)
{
  return(us_distance_back_center);
}
unsigned char Model::getDistanceBackRight(void)
{
  return(us_distance_back_right);
}
//** Gps
double Model::getLongitude(void)
{
  return(longitude);
}
double Model::getLatitude(void)
{
  return(latitude);
}
int Model::getModeGps(void)
{
  return(mode_gps);
}

//** IMU
int Model::getHeadingImu(void)
{
  return(heading_imu);
}

//** Music
int Model::getCptMusic(void)
{
  return(cpt_music);
}









//******** ADD ********//

void Model::addPwmMotorBack(unsigned char val)
{
  pwm_motor_back = val;
}

//** Steering Wheel
void Model::addStateSteeringWheel(unsigned char val)
{
  state_steering_wheel = val;
}

//** Encoder
void Model::addEncoderWheelBackLeft(float val)
{
  encoder_wheel_back_left = val;
}
void Model::addEncoderWheelBackRight(float val)
{
  encoder_wheel_back_right = val;
}
void Model::addDistance(float val)
{
  distance = val;
}

//** US Validity
void Model::addValidityFrontLeft(unsigned char val)
{
  us_validity_front_left = val;
}
void Model::addValidityFrontCenter(unsigned char val)
{
  us_validity_front_center = val;
}
void Model::addValidityFrontRight(unsigned char val)
{
  us_validity_front_right = val;
}
void Model::addValidityBackLeft(unsigned char val)
{
  us_validity_back_left = val;
}
void Model::addValidityBackCenter(unsigned char val)
{
  us_validity_back_center = val;
}
void Model::addValidityBackRight(unsigned char val)
{
  us_validity_back_left = val;
}

void Model::addDistanceFrontLeft(unsigned char val)
{
  us_distance_front_left = val;
}
void Model::addDistanceFrontCenter(unsigned char val)
{
  us_distance_front_center = val;
}
void Model::addDistanceFrontRight(unsigned char val)
{
  us_distance_front_right = val;
}
void Model::addDistanceBackLeft(unsigned char val)
{
  us_distance_back_left = val;
}
void Model::addDistanceBackCenter(unsigned char val)
{
  us_distance_back_center = val;
}
void Model::addDistanceBackRight(unsigned char val)
{
  us_distance_back_right = val;
}
//** Gps
void Model::addLongitude(double val)
{
  longitude = val;
}
void Model::addLatitude(double val)
{
  latitude = val;
}
void Model::addModeGps(int val)
{
  mode_gps = val;
}
//** IMU
void Model::addHeadingImu(int val)
{
  heading_imu = val;
}
//** Music
void Model::addCptMusic(int val)
{
  cpt_music = val;
}

void Model::printEncoder()
{
	cout << "Distance Left : " << encoder_wheel_back_left << endl;
  cout << "Distance Right : " << encoder_wheel_back_right << endl;
  cout << "Distance : " << distance << endl;
	cout << "Erreur : " << encoder_wheel_back_left - encoder_wheel_back_right << endl;
}

void Model::printModel(void)
{
  cout << "  CAR STATE  " << endl << endl;
  cout << "Pwm : " << (int)pwm_motor_back << endl;
  cout << "Steering wheel state : " << (int)state_steering_wheel << endl;
  cout << "Distance Left : " << (float)encoder_wheel_back_left << endl;
  cout << "Distance Right : " << (float)encoder_wheel_back_right << endl;
  cout << "Distance : " << (float)distance << endl;
  cout << "Us front left, Validity : " << (int)us_validity_front_left << ", Distance : " << (int)us_distance_front_left <<"cm " << endl;
  cout << "Us front center, Validity : " << (int)us_validity_front_center << ", Distance : " << (int)us_distance_front_center <<"cm " << endl;
  cout << "Us front right, Validity : " << (int)us_validity_front_right << ", Distance : " << (int)us_distance_front_right <<"cm " << endl;

  cout << "Us back left, Validity : " << (int)us_validity_back_left << ", Distance : " << (int)us_distance_back_left <<"cm " << endl;
  cout << "Us back center, Validity : " << (int)us_validity_back_center << ", Distance : " << (int)us_distance_back_center <<"cm " << endl;
  cout << "Us back right, Validity : " << (int)us_validity_back_right << ", Distance : " << (int)us_distance_back_right <<"cm " << endl;
}

void Model::printGps(void)
{
  cout << "Longitude : "<< longitude << endl;
  cout << "Latitude : " << latitude << endl;
  cout << "Mode Gps : " << mode_gps << endl;

  cout << "cap : " << heading_imu<< endl;
}
