#ifndef CAR_H
#define CAR_H

class Car
{
  //private:
  public:
  Car(); // Constructor
  //~Car(); // Destructor

  //******** GET ********//
  //** PWM
  unsigned char Car::getPwmMotorBack(void);
  //** Steering Wheel
  unsigned char Car::getStateSteeringWheel(void);
  //** Encodeur
  float Car::getEncodeurWheelBackLeft(void);
  float Car::getEncodeurWheelBackRight(void);
  //** US Validity
  unsigned char Car::getValidityFrontLeft(void);
  unsigned char Car::getValidityFrontCenter(void);
  unsigned char Car::getValidityFrontRight(void);
  unsigned char Car::getValidityBackLeft(void);
  unsigned char Car::getValidityBackCenter(void);
  unsigned char Car::getValidityBackRight(void);
  //** Distance
  unsigned char Car::getDistanceFrontLeft(void);
  unsigned char Car::getDistanceFrontCenter(void);
  unsigned char Car::getDistanceFrontRight(void);
  unsigned char Car::getDistanceBackLeft(void);
  unsigned char Car::getDistanceBackCenter(void);
  unsigned char Car::getDistanceBackRight(void);

  void printEncodeur(void);
  void printCar(void);

  //private:

  unsigned char pwm_motor_back;
  unsigned char state_steering_wheel;

  /*unsigned char encodeur_wheel_back_left_100m;
  unsigned char encodeur_wheel_back_left_1m;
  unsigned char encodeur_wheel_back_left_1cm;
  unsigned char encodeur_wheel_back_right_100m;
  unsigned char encodeur_wheel_back_right_1m;
  unsigned char encodeur_wheel_back_right_1cm;*/

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
