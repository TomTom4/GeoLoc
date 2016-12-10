#ifndef CAR_H
#define CAR_H

class Car
{
  //private:
  public:
  Car(); // Constructor
  //~Car(); // Destructor
  unsigned char getData(int num);
  void addData(int num, unsigned char val);

  private:

  unsigned char pwm_motor_ar_d;
  unsigned char pwm_motor_ar_g;
  unsigned char cpt_dir;
  unsigned char encodeur_wheel_ar_d;
  unsigned char encodeur_wheel_ar_g;

  unsigned char us_id_av_d;
  unsigned char us_validity_av_d;
  unsigned char us_distance_av_d;

  unsigned char us_id_av_c;
  unsigned char us_validity_av_c;
  unsigned char us_distance_av_c;

  unsigned char us_id_av_g;
  unsigned char us_validity_av_g;
  unsigned char us_distance_av_g;

  unsigned char us_id_ar_d;
  unsigned char us_validity_ar_d;
  unsigned char us_distance_ar_d;

  unsigned char us_id_ar_c;
  unsigned char us_validity_ar_c;
  unsigned char us_distance_ar_c;

  unsigned char us_id_ar_g;
  unsigned char us_validity_ar_g;
  unsigned char us_distance_ar_g;

  // And any other protected methods.
  /*
  *static Car& Instance()

  // delete copy and move constructors and assign operators
  Car(Car const&) = delete;             // Copy construct
  Car(Car&&) = delete;                  // Move construct
  Car& operator=(Car const&) = delete;  // Copy assign
  Car& operator=(Car &&) = delete;      // Move assign
  */

// Any other public methods

};

#endif
