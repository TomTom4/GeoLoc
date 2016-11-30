#ifndef MOVE_CAR_H
#define MOVE_CAR_H

/* DECLARATION EXTERNE */
//extern const int SPI_DATA_SIZE;

extern const int STOP_ALL;
extern const int STOP_FRONT_BACK;
extern const int STOP_LEFT_RIGHT;
extern const int MOVE_FRONT;
extern const int MOVE_BACK;
extern const int MOVE_LEFT;
extern const int MOVE_RIGHT;
extern const int CAPTOR;

extern char table_spi[10][10/*SPI_DATA_SIZE*/];
extern char data_spi_RW[10/*SPI_DATA_SIZE*/];


void stop_all(void);
void stop_front_back(void);
void stop_left_right(void);
void move_front(void);
void move_back(void);
void move_left(void);
void move_right(void);
void captor(void);
#endif
