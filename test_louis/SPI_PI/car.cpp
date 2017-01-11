#include <stdio.h>
#include <iostream>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "car.hpp"
#include "const.hpp"


using namespace std;

Car::Car()
{
  pwm_motor_back = 0;
  state_steering_wheel = 6;
  encodeur_wheel_back_left = 0.0;
  encodeur_wheel_back_right = 0.0;

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
}

//******** GET ********//

//** PWM
unsigned char Car::getPwmMotorBack(void)
{
  return(pwm_motor_back);
}

//** Steering Wheel
unsigned char Car::getStateSteeringWheel(void)
{
  return(state_steering_wheel);
}

//** Encodeur
float Car::getEncodeurWheelBackLeft(void)
{
  return(encodeur_wheel_back_left);
}
float Car::getEncodeurWheelBackRight(void)
{
  return(encodeur_wheel_back_right);
}

//** US Validity
unsigned char Car::getValidityFrontLeft(void)
{
  return(us_validity_front_left);
}
unsigned char Car::getValidityFrontCenter(void)
{
  return(us_validity_front_center);
}
unsigned char Car::getValidityFrontRight(void)
{
  return(us_validity_front_right);
}
unsigned char Car::getValidityBackLeft(void)
{
  return(us_validity_back_left);
}
unsigned char Car::getValidityBackCenter(void)
{
  return(us_validity_back_center);
}
unsigned char Car::getValidityBackRight(void)
{
  return(us_validity_back_left);
}

//** Distance
unsigned char Car::getDistanceFrontLeft(void)
{
  return(us_distance_front_left);
}
unsigned char Car::getDistanceFrontCenter(void)
{
  return(us_distance_front_center);
}
unsigned char Car::getDistanceFrontRight(void)
{
  return(us_distance_front_right);
}
unsigned char Car::getDistanceBackLeft(void)
{
  return(us_distance_back_left);
}
unsigned char Car::getDistanceBackCenter(void)
{
  return(us_distance_back_center);
}
unsigned char Car::getDistanceBackRight(void)
{
  return(us_distance_back_right);
}

//******** ADD ********//

void Car::addPwmMotorBack(unsigned char val)
{
  pwm_motor_back = val;
}

//** Steering Wheel
void Car::addStateSteeringWheel(unsigned char val)
{
  state_steering_wheel = val;
}

//** Encodeur
void Car::addEncodeurWheelBackLeft(float val)
{
  encodeur_wheel_back_left = val;
}
void Car::addEncodeurWheelBackRight(float val)
{
  encodeur_wheel_back_right = val;
}

//** US Validity
void Car::addValidityFrontLeft(unsigned char val)
{
  us_validity_front_left = val;
}
void Car::addValidityFrontCenter(unsigned char val)
{
  us_validity_front_center = val;
}
void Car::addValidityFrontRight(unsigned char val)
{
  us_validity_front_right = val;
}
void Car::addValidityBackLeft(unsigned char val)
{
  us_validity_back_left = val;
}
void Car::addValidityBackCenter(unsigned char val)
{
  us_validity_back_center = val;
}
void Car::addValidityBackRight(unsigned char val)
{
  us_validity_back_left = val;
}

void Car::addDistanceFrontLeft(unsigned char val)
{
  us_distance_front_left = val;
}
void Car::addDistanceFrontCenter(unsigned char val)
{
  us_distance_front_center = val;
}
void Car::addDistanceFrontRight(unsigned char val)
{
  us_distance_front_right = val;
}
void Car::addDistanceBackLeft(unsigned char val)
{
  us_distance_back_left = val;
}
void Car::addDistanceBackCenter(unsigned char val)
{
  us_distance_back_center = val;
}
void Car::addDistanceBackRight(unsigned char val)
{
  us_distance_back_right = val;
}

void Car::printEncodeur()
{
	cout << "Distance Left : " << encodeur_wheel_back_left << endl;
  cout << "Distance Right : " << encodeur_wheel_back_right << endl;
	cout << "Erreur : " << encodeur_wheel_back_left - encodeur_wheel_back_right << endl;
}

void Car::printCar(void)
{
  cout << "  CAR STATE  " << endl << endl;
  cout << "Pwm : " << (int)pwm_motor_back << endl;
  cout << "Steering wheel state : " << (int)state_steering_wheel << endl;
  cout << "Distance Left : " << (float)encodeur_wheel_back_left << endl;
  cout << "Distance Right : " << (float)encodeur_wheel_back_right << endl;
  cout << "Us front left, Validity : " << (int)us_validity_front_left << ", Distance : " << (int)us_distance_front_left <<"cm " << endl;
  cout << "Us front center, Validity : " << (int)us_validity_front_center << ", Distance : " << (int)us_distance_front_center <<"cm " << endl;
  cout << "Us front right, Validity : " << (int)us_validity_front_right << ", Distance : " << (int)us_distance_front_right <<"cm " << endl;

  cout << "Us back left, Validity : " << (int)us_validity_back_left << ", Distance : " << (int)us_distance_back_left <<"cm " << endl;
  cout << "Us back center, Validity : " << (int)us_validity_back_center << ", Distance : " << (int)us_distance_back_center <<"cm " << endl;
  cout << "Us back right, Validity : " << (int)us_validity_back_right << ", Distance : " << (int)us_distance_back_right <<"cm " << endl;
}
