#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "spi.h"

int spiDataRW(char* data, int lenght)
{
	return wiringPiSPIDataRW(0,(unsigned char*)data,lenght);
}

int spiPrintRW(void)
{
	int ret;
	printf("------------------------\n");
	printf("Chaine a envoyer : %s\n",data_spi_RW);
	ret = spiDataRW(data_spi_RW,10/*SPI_DATA_SIZE*/);
	printf("Capteur n°: %d Validite: %d Distance: %dcm\n", data_spi_RW[0],data_spi_RW[1],data_spi_RW[2]);
	printf("Capteur n°: %d Validite: %d Distance: %dcm\n", data_spi_RW[3],data_spi_RW[4],data_spi_RW[5]);
	printf("Capteur n°: %d Validite: %d Distance: %dcm\n", data_spi_RW[6],data_spi_RW[7],data_spi_RW[8]);
	return ret;
}
