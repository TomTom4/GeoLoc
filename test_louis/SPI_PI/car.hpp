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
  unsigned char getPwmMotorBack(void);
  //** Steering Wheel
  unsigned char getStateSteeringWheel(void);
  //** Encodeur
  float getEncodeurWheelBackLeft(void);
  float getEncodeurWheelBackRight(void);
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

//** PWM
void addPwmMotorBack(unsigned char val);

//** Steering Wheel
void addStateSteeringWheel(unsigned char val);

//** Encodeur
void addEncodeurWheelBackLeft(float val);
void addEncodeurWheelBackRight(float val);

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

  void printEncodeur(void);
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
