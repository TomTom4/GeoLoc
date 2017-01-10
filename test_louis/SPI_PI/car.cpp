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

  us_id_front_left = US_ID_FRONT_LEFT_VAL;
  us_validity_front_left = 0;
  us_distance_front_left = 0xFF;

  us_id_front_center = US_ID_FRONT_CENTER_VAL;
  us_validity_front_center = 0;
  us_distance_front_center = 0xFF;

  us_id_front_right = US_ID_FRONT_RIGHT_VAL;
  us_validity_front_right = 0;
  us_distance_front_right = 0xFF;

  us_id_back_left = US_ID_BACK_LEFT_VAL;
  us_validity_back_left = 0;
  us_distance_back_left = 0xFF;

  us_id_back_center = US_ID_BACK_CENTER_VAL;
  us_validity_back_center = 0;
  us_distance_back_center = 0xFF;

  us_id_back_right = US_ID_BACK_RIGHT_VAL;
  us_validity_back_right = 0;
  us_distance_back_right = 0xFF;
}

unsigned char Car::getData(int num)
{
  switch(num)
  {
    case PWM_MOTOR_BACK:                return(pwm_motor_back); break;
    case STATE_STEERING_WHEEL:          return(state_steering_wheel); break;
    case ENCODEUR_WHEEL_BACK_LEFT_100M:
    case ENCODEUR_WHEEL_BACK_LEFT_1M:
    case ENCODEUR_WHEEL_BACK_LEFT_1CM: return(encodeur_wheel_back_left); break;

    case ENCODEUR_WHEEL_BACK_RIGHT_100M:
    case ENCODEUR_WHEEL_BACK_RIGHT_1M:
    case ENCODEUR_WHEEL_BACK_RIGHT_1CM: return(encodeur_wheel_back_right); break;

    case US_ID_FRONT_LEFT:          return(us_id_front_left); break;
    case US_VALIDITY_FRONT_LEFT:    return(us_validity_front_left); break;
    case US_DISTANCE_FRONT_LEFT:    return(us_distance_front_left); break;

    case US_ID_FRONT_CENTER:        return(us_id_front_center); break;
    case US_VALIDITY_FRONT_CENTER:  return(us_validity_front_center); break;
    case US_DISTANCE_FRONT_CENTER:  return(us_distance_front_center); break;

    case US_ID_FRONT_RIGHT:         return(us_id_front_right); break;
    case US_VALIDITY_FRONT_RIGHT:   return(us_validity_front_right); break;
    case US_DISTANCE_FRONT_RIGHT:   return(us_distance_front_right); break;

    case US_ID_BACK_LEFT:           return(us_id_back_left); break;
    case US_VALIDITY_BACK_LEFT:     return(us_validity_back_left); break;
    case US_DISTANCE_BACK_LEFT:     return(us_distance_back_left); break;

    case US_ID_BACK_CENTER:         return(us_id_back_center); break;
    case US_VALIDITY_BACK_CENTER:   return(us_validity_back_center); break;
    case US_DISTANCE_BACK_CENTER:   return(us_distance_back_center); break;

    case US_ID_BACK_RIGHT:          return(us_id_back_right); break;
    case US_VALIDITY_BACK_RIGHT:    return(us_validity_back_right); break;
    case US_DISTANCE_BACK_RIGHT:    return(us_distance_back_right); break;
  }
return (0);
}

void Car::addDataEncodeur(void)
{
  encodeur_wheel_back_left = (float)encodeur_wheel_back_left_100m*100.0 + (float)encodeur_wheel_back_left_1m + (float)encodeur_wheel_back_left_1cm*0.01;
  encodeur_wheel_back_right = (float)encodeur_wheel_back_right_100m*100.0 + (float)encodeur_wheel_back_right_1m + (float)encodeur_wheel_back_right_1cm*0.01;
}

void Car::addData(unsigned char num, unsigned char val)
{
  switch(num)
  {
    case PWM_MOTOR_BACK:                pwm_motor_back = val; break;
    case STATE_STEERING_WHEEL:          state_steering_wheel = val; break;

    case ENCODEUR_WHEEL_BACK_LEFT_100M:  encodeur_wheel_back_left_100m = val; break;
    case ENCODEUR_WHEEL_BACK_LEFT_1M:  encodeur_wheel_back_left_1m = val; break;
    case ENCODEUR_WHEEL_BACK_LEFT_1CM:  encodeur_wheel_back_left_1cm = val; break;

    case ENCODEUR_WHEEL_BACK_RIGHT_100M: encodeur_wheel_back_right_100m = val; break;
    case ENCODEUR_WHEEL_BACK_RIGHT_1M: encodeur_wheel_back_right_1m = val; break;
    case ENCODEUR_WHEEL_BACK_RIGHT_1CM: encodeur_wheel_back_right_1cm = val; break;

    case US_ID_FRONT_LEFT:              us_id_front_left = val; break;
    case US_VALIDITY_FRONT_LEFT:        us_validity_front_left = val; break;
    case US_DISTANCE_FRONT_LEFT:        us_distance_front_left = val; break;

    case US_ID_FRONT_CENTER:            us_id_front_center = val; break;
    case US_VALIDITY_FRONT_CENTER:      us_validity_front_center = val; break;
    case US_DISTANCE_FRONT_CENTER:      us_distance_front_center = val; break;

    case US_ID_FRONT_RIGHT:             us_id_front_right = val; break;
    case US_VALIDITY_FRONT_RIGHT:       us_validity_front_right = val; break;
    case US_DISTANCE_FRONT_RIGHT:       us_distance_front_right = val; break;

    case US_ID_BACK_LEFT:               us_id_back_left = val; break;
    case US_VALIDITY_BACK_LEFT:         us_validity_back_left = val; break;
    case US_DISTANCE_BACK_LEFT:         us_distance_back_left = val; break;

    case US_ID_BACK_CENTER:             us_id_back_center = val; break;
    case US_VALIDITY_BACK_CENTER:       us_validity_back_center = val; break;
    case US_DISTANCE_BACK_CENTER:       us_distance_back_center = val; break;

    case US_ID_BACK_RIGHT:               us_id_back_right = val; break;
    case US_VALIDITY_BACK_RIGHT:         us_validity_back_right = val; break;
    case US_DISTANCE_BACK_RIGHT:         us_distance_back_right = val; break;
  }
}

void Car::printEncodeur()
{
	cout << "Distance Left : " << (float)encodeur_wheel_back_left << endl;
  	cout << "Distance Right : " << (float)encodeur_wheel_back_right << endl;
	cout << "Erreur : " << (float)encodeur_wheel_back_left - (float)encodeur_wheel_back_right << endl;
}

void Car::printCar(void)
{
  cout << "\tCAR STATE\n" << endl;
  /*cout << "Pwm : " << (int)pwm_motor_back << endl;
  cout << "Steering wheel state : " << (int)state_steering_wheel << endl;
  cout << "Distance Left : " << (float)encodeur_wheel_back_left << endl;
  cout << "Distance Right : " << (float)encodeur_wheel_back_right << endl;
  cout << "Us front left, Validity : " << (int)us_validity_front_left << ", Distance : " << (int)us_distance_front_left <<"cm " << endl;
  cout << "Us front center, Validity : " << (int)us_validity_front_center << ", Distance : " << (int)us_distance_front_center <<"cm " << endl;
  cout << "Us front right, Validity : " << (int)us_validity_front_right << ", Distance : " << (int)us_distance_front_right <<"cm " << endl;

  cout << "Us back left, Validity : " << (int)us_validity_back_left << ", Distance : " << (int)us_distance_back_left <<"cm " << endl;
  cout << "Us back center, Validity : " << (int)us_validity_back_center << ", Distance : " << (int)us_distance_back_center <<"cm " << endl;
  cout << "Us back right, Validity : " << (int)us_validity_back_right << ", Distance : " << (int)us_distance_back_right <<"cm " << endl;
*/
}

/*Car& Car::Instance();
{
    // Since it's a static variable, if the class has already been created,
    // It won't be created again.
    // And it **is** thread-safe in C++11.
    static Car myInstance;
    // Return a reference to our instance.
    return myInstance;
}*/
