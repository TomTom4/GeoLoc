#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "spi.h"
#include "move_car.h"

MoveCar::MoveCar(Spi* spi)
{
	spi_move_car = spi;
	STOP_ALL = 0;
	STOP_FRONT_BACK = 1;
	STOP_LEFT_RIGHT = 2;
	MOVE_FRONT = 3;
	MOVE_BACK = 4;
	MOVE_LEFT = 5;
	MOVE_RIGHT = 6;
	CAPTOR = 7;
	RIEN = 8;
	CENTER = 9;
}

void MoveCar::rien(void)
{
	spi_move_car->spiCopyCmd(RIEN);
	while(!spi_move_car->spiPrintRW());
}
void MoveCar::stopAll(void)
{
	spi_move_car->spiCopyCmd(STOP_ALL);
	while(!spi_move_car->spiPrintRW());
}

void MoveCar::stopFrontBack(void)
{
	spi_move_car->spiCopyCmd(STOP_FRONT_BACK);
	while(!spi_move_car->spiPrintRW());
}

void MoveCar::stopLeftRight(void)
{
 	spi_move_car->spiCopyCmd(STOP_LEFT_RIGHT);
	while(!spi_move_car->spiPrintRW());
}

void MoveCar::moveFront(void)
{
	//printf("Move front\n");
	//printf("tamp\n");
	spi_move_car->spiCopyCmd(MOVE_FRONT);
	//printf("Move front cpy ok\n");
	//printf("tamp\n");
	while(!spi_move_car->spiPrintRW());
}

void MoveCar::moveBack(void)
{
	spi_move_car->spiCopyCmd(MOVE_BACK);
	while(!spi_move_car->spiPrintRW());
}

void MoveCar::moveLeft(void)
{
	spi_move_car->spiCopyCmd(MOVE_LEFT);
	while(!spi_move_car->spiPrintRW());
}

void MoveCar::moveRight(void)
{
	spi_move_car->spiCopyCmd(MOVE_RIGHT);
	while(!spi_move_car->spiPrintRW());
}

void MoveCar::captor(void)
{
	spi_move_car->spiCopyCmd(CAPTOR);
	while(!spi_move_car->spiPrintRW());
}

void MoveCar::center(void)
{
	spi_move_car->spiCopyCmd(CENTER);
	while(!spi_move_car->spiPrintRW());
}
