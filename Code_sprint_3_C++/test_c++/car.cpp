#include <stdio.h>
//#include <wiringPi.h>
//#include <wiringPiSPI.h>

#include "car.h"

using namespace std;

Car::Car()
{
  pwm_motor_ar_d = 50;
  pwm_motor_ar_g = 50;
  cpt_dir = 4;
  encodeur_wheel_ar_d = 0;
  encodeur_wheel_ar_g = 0;

  us_id_av_d = 0x01;
  us_validity_av_d = 0;
  us_distance_av_d = 0xFF;

  us_id_av_c = 0x02;
  us_validity_av_c = 0;
  us_distance_av_c = 0xFF;

  us_id_av_g = 0x03;
  us_validity_av_g = 0;
  us_distance_av_g = 0xFF;

  us_id_ar_d = 0x04;
  us_validity_ar_d = 0;
  us_distance_ar_d = 0xFF;

  us_id_ar_c = 0x05;
  us_validity_ar_c = 0;
  us_distance_ar_c = 0xFF;

  us_id_ar_g = 0x06;
  us_validity_ar_g = 0;
  us_distance_ar_g = 0xFF;
}

unsigned char getData(int num)
{
  switch(num)
  {
    case 1: return(pwm_motor_ar_d); break;
    case 2: return(pwm_motor_ar_g); break;
    case 3: return(cpt_dir); break;
    case 4: return(encodeur_wheel_ar_d); break;
    case 5: return(encodeur_wheel_ar_g); break;

    case 6: return(us_id_av_d); break;
    case 7: return(us_validity_av_d); break;
    case 8: return(us_distance_av_d); break;

    case 9: return(us_id_av_c); break;
    case 10: return(us_validity_av_c); break;
    case 11: return(us_distance_av_c); break;

    case 12: return(us_id_av_g); break;
    case 13: return(us_validity_av_g); break;
    case 14: return(us_distance_av_g); break;

    case 15: return(us_id_ar_d); break;
    case 16: return(us_validity_ar_d); break;
    case 17: return(us_distance_ar_d); break;

    case 18: return(us_id_ar_c); break;
    case 19: return(us_validity_ar_c); break;
    case 20: return(us_distance_ar_c); break;

    case 21: return(us_id_ar_g); break;
    case 22: return(us_validity_ar_g); break;
    case 23: return(us_distance_ar_g); break;
  }
}

void addData(int num, unsigned int val)
{
  switch(num)
  {
    case 1: pwm_motor_ar_d = val; break;
    case 2: pwm_motor_ar_g = val; break;
    case 3: cpt_dir = val; break;
    case 4: encodeur_wheel_ar_d = val; break;
    case 5: encodeur_wheel_ar_g = val; break;

    case 6: us_id_av_d = val; break;
    case 7: us_validity_av_d = val; break;
    case 8: us_distance_av_d = val; break;

    case 9: us_id_av_c = val; break;
    case 10: us_validity_av_c = val; break;
    case 11: us_distance_av_c = val; break;

    case 12: us_id_av_g = val; break;
    case 13: us_validity_av_g = val; break;
    case 14: us_distance_av_g = val; break;

    case 15: us_id_ar_d = val; break;
    case 16: us_validity_ar_d = val; break;
    case 17: us_distance_ar_d = val; break;

    case 18: us_id_ar_c = val; break;
    case 19: us_validity_ar_c = val; break;
    case 20: us_distance_ar_c = val; break;

    case 21: us_id_ar_g = val; break;
    case 22: us_validity_ar_g = val; break;
    case 23: us_distance_ar_g = val; break;
  }
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
