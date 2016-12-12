#ifndef MOVE_CAR_H
#define MOVE_CAR_H

#include "spi.h"

class MoveCar
{
private:
  Spi* spi_move_car;
  int STOP_ALL;
  int STOP_FRONT_BACK;
  int STOP_LEFT_RIGHT;
  int MOVE_FRONT;
  int MOVE_BACK;
  int MOVE_LEFT;
  int MOVE_RIGHT;
  int CAPTOR;
  int RIEN;
  int CENTER;
public:
  MoveCar(Spi* spi);
  void rien(void);
  void stopAll(void);
  void stopFrontBack(void);
  void stopLeftRight(void);
  void moveFront(void);
  void moveBack(void);
  void moveLeft(void);
  void moveRight(void);
  void captor(void);
  void center(void);
};

#endif
