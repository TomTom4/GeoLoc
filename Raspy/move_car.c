#include <string.h>

#include "move_car.h"
#include "spi.h"

/* DECLARATIONS GLOBALES */

void stop_all(void)
{
	strcpy(data_spi_RW,table_spi[STOP_ALL]);
	while(!spiPrintRW());			
}

void stop_front_back(void)
{
 	strcpy(data_spi_RW,table_spi[STOP_FRONT_BACK]);
	while(!spiPrintRW());			
}

void stop_left_right(void)
{
 	strcpy(data_spi_RW,table_spi[STOP_LEFT_RIGHT]);
	while(!spiPrintRW());			
}

void move_front(void)
{
	strcpy(data_spi_RW,table_spi[MOVE_FRONT]);
	while(!spiPrintRW());			
}

void move_back(void)
{
	strcpy(data_spi_RW,table_spi[MOVE_BACK]);
	while(!spiPrintRW());			
}

void move_left(void)
{
	strcpy(data_spi_RW,table_spi[MOVE_LEFT]);
	while(!spiPrintRW());			
}

void move_right(void)
{
	strcpy(data_spi_RW,table_spi[MOVE_RIGHT]);
	while(!spiPrintRW());			
}

void captor(void)
{
	strcpy(data_spi_RW,table_spi[CAPTOR]);
	while(!spiPrintRW());			
}
