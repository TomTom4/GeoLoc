#ifndef SPI_HPP
#define SPI_HPP

class Spi /*:: public Singleton*/
{
public:
  Spi(Car* voit);
  void readWriteData();
  void clearString();
  void addDataString();
  void extractUsSensor(int offset_string);
  void extractDataString();
  void extractEncodeur();
  void majCar();

private:
  unsigned char lenght_string;
  unsigned char* string_spi;
  unsigned char beacon_rasp_start; // 0110b & 1001b
  unsigned char beacon_rasp_end; // 1010b & 0101b
  unsigned char beacon_stm_start; // 0011b & 1100b
  unsigned char beacon_stm_end; // 1110b & 0001b
  float encodeur_left;
  float encodeur_right;
  Car* voiture;

  const unsigned char = ; //

};

      const unsigned char BEACON_START = 0 ;         //beacon_start (rasp or stm)
      const unsigned char PWM_MOTOR_BACK = 1;
      const unsigned char STATE_STEERING_WHEEL = 2;

      /** encodeur wheel AR L **/
      const unsigned char ENCODEUR_WHEEL_BACK_LEFT_100M = 3; //Counter 100m : 0 -> 99
      const unsigned char ENCODEUR_WHEEL_BACK_LEFT_1M = 4;   //Counter 1m : 0 -> 99
      const unsigned char ENCODEUR_WHEEL_BACK_LEFT_1CM = 5;  //counter 0.01m : 0 -> 99

      /** encodeur wheel AR D **/
      const unsigned char ENCODEUR_WHEEL_BACK_RIGHT_100M = 6; //Counter 100m : 0 -> 99
      const unsigned char ENCODEUR_WHEEL_BACK_RIGHT_1M = 7;   //Counter 1m : 0 -> 99
      const unsigned char ENCODEUR_WHEEL_BACK_RIGHT_1CM = 8;  //counter 0.01m : 0 -> 99

      /** US sensors **/
      const unsigned char US_ID_FRONT_LEFT = 9;
      const unsigned char US_VALIDITY_FRONT_LEFT = 10;
      const unsigned char US_DISTANCE_FRONT_LEFT = 11;
      const unsigned char US_IS_FRONT_CENTER = 12;
      const unsigned char US_VALIDITY_FRONT_CENTER = 13;
      const unsigned char US_DISTANCE_FRONT_CENTER = 14;
      const unsigned char US_IS_FRONT_RIGHT = 15;
      const unsigned char US_VALIDITY_FRONT_RIGHT = 16;
      const unsigned char US_DISTANCE_FRONT_RIGHT = 17;

      const unsigned char US_IS_BACK_LEFT = 18;
      const unsigned char US_VALIDITY_BACK_LEFT = 19;
      const unsigned char US_DISTANCE_BACK_LEFT = 20;
      const unsigned char US_IS_BACK_CENTER = 21;
      const unsigned char US_VALIDITY_BACK_CENTER = 22;
      const unsigned char US_DISTANCE_BACK_CENTER = 23;
      const unsigned char US_IS_BACK_RIGHT = 24;
      const unsigned char US_VALIDITY_BACK_RIGHT = 25;
      const unsigned char US_DISTANCE_BACK_RIGHT = 26;

      const unsigned char BEACON_STOP = 27; //beacon_stop (rasp or stm)

#endif
