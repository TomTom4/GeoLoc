#include <stdio.h>
//#include <wiringPi.h>
//#include <wiringPiSPI.h>

#include "car.hpp"

using namespace std;

Car::Car()
{
  pwm_motor_back = 50;
  state_steering_wheel = 4;
  encodeur_wheel_ar_l = 0.0;
  encodeur_wheel_ar_r = 0.0;

  us_id_av_l = 0x01;
  us_validity_av_l = 0;
  us_listance_av_l = 0xFF;

  us_id_av_c = 0x02;
  us_validity_av_c = 0;
  us_listance_av_c = 0xFF;

  us_id_av_r = 0x03;
  us_validity_av_r = 0;
  us_listance_av_r = 0xFF;

  us_id_ar_l = 0x04;
  us_validity_ar_l = 0;
  us_listance_ar_l = 0xFF;

  us_id_ar_c = 0x05;
  us_validity_ar_c = 0;
  us_listance_ar_c = 0xFF;

  us_id_ar_r = 0x06;
  us_validity_ar_r = 0;
  us_listance_ar_r = 0xFF;
}

unsigned char Car::getData(int num)
{
  switch(num)
  {
    case 1: return(pwm_motor_back); break;
    case 2: return(pwm_motor_ar_r); break;
    case 3: return(state_steering_wheel); break;
    case 4: return(encodeur_wheel_ar_l); break;
    case 5: return(encodeur_wheel_ar_r); break;

    case 6: return(us_id_av_l); break;
    case 7: return(us_validity_av_l); break;
    case 8: return(us_listance_av_l); break;

    case 9: return(us_id_av_c); break;
    case 10: return(us_validity_av_c); break;
    case 11: return(us_listance_av_c); break;

    case 12: return(us_id_av_r); break;
    case 13: return(us_validity_av_r); break;
    case 14: return(us_listance_av_r); break;

    case 15: return(us_id_ar_l); break;
    case 16: return(us_validity_ar_l); break;
    case 17: return(us_listance_ar_l); break;

    case 18: return(us_id_ar_c); break;
    case 19: return(us_validity_ar_c); break;
    case 20: return(us_listance_ar_c); break;

    case 21: return(us_id_ar_r); break;
    case 22: return(us_validity_ar_r); break;
    case 23: return(us_listance_ar_r); break;
  }
}

void Car::addDataEncodeur(float encodeur_left, float encodeur_right)
{
  encodeur_wheel_ar_l = encodeur_left;
  encodeur_wheel_ar_r = encodeur_right;
}

void Car::addData(unsigned char num, unsigned char val)
{
  switch(num)
  {
    case 1: pwm_motor_back = val; break;
    case 2: pwm_motor_ar_r = val; break;
    case 3: state_steering_wheel = val; break;
    case 4: encodeur_wheel_ar_l = val; break;
    case 5: encodeur_wheel_ar_r = val; break;

    case 6: us_id_av_l = val; break;
    case 7: us_validity_av_l = val; break;
    case 8: us_listance_av_l = val; break;

    case 9: us_id_av_c = val; break;
    case 10: us_validity_av_c = val; break;
    case 11: us_listance_av_c = val; break;

    case 12: us_id_av_r = val; break;
    case 13: us_validity_av_r = val; break;
    case 14: us_listance_av_r = val; break;

    case 15: us_id_ar_l = val; break;
    case 16: us_validity_ar_l = val; break;
    case 17: us_listance_ar_l = val; break;

    case 18: us_id_ar_c = val; break;
    case 19: us_validity_ar_c = val; break;
    case 20: us_listance_ar_c = val; break;

    case 21: us_id_ar_r = val; break;
    case 22: us_validity_ar_r = val; break;
    case 23: us_listance_ar_r = val; break;
  }
}

void Car::printCar(void)
{
  cout << "\tCAR STATE\n" << endl;
  cout << "Pwm : " << pwm_motor_back << endl;
  cout << "Steering wheel state : " << state_steering_wheel << endl;
  cout << "Distance Left : " << encodeur_wheel_back_left << endl;
  cout << "Distance Right : " << encodeur_wheel_back_right << endl;
  cout << "Us front left, Validity : " << vus_validity_front_left << ", Distance : " << us_distance_front_left <<"cm "endl;
  cout << "Us front center, Validity : " << vus_validity_front_center << ", Distance : " << us_distance_front_center <<"cm "endl;
  cout << "Us front right, Validity : " << vus_validity_front_right << ", Distance : " << us_distance_front_right <<"cm "endl;

  cout << "Us back left, Validity : " << vus_validity_back_left << ", Distance : " << us_distance_back_left <<"cm "endl;
  cout << "Us back center, Validity : " << vus_validity_back_center << ", Distance : " << us_distance_back_center <<"cm "endl;
  cout << "Us back right, Validity : " << vus_validity_back_right << ", Distance : " << us_distance_back_right <<"cm "endl;

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
