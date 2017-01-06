#ifndef CAR_H
#define CAR_H

class Car
{
  //private:
  public:
  Car(); // Constructor
  //~Car(); // Destructor
  unsigned char getData(int num);
  void addData(unsigned char num, unsigned char val);
  void addDataEncodeur(float encodeur_left, float encodeur_right);
  void printCar(void);

  private:

  unsigned char pwm_motor_back;
  unsigned char state_steering_wheel;
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
