#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "spi.h"

Spi::Spi()
{
	int j, i;
	char carac = '0';
	for(i = 0; i < SPI_CMD_SIZE; i++)
	{
		for(j = 0; j < SPI_DATA_SIZE-1; j++)
		{
			table_spi[i][j] = carac+i;
		}
		table_spi[i][j] = '\0';
	}
}

void Spi::spiCopyCmd(int cmd)
{
	//printf(" table cmd = %s", table_spi[cmd]);
	strcpy(data_spi_RW,table_spi[cmd]);
}

int Spi::spiDataRW(char* data, int lenght)
{
	return wiringPiSPIDataRW(0,(unsigned char*)data,lenght);
}

int Spi::spiPrintRW(void)
{
	int ret;
	/*printf("------------------------\n");
	printf("Chaine a envoyer : %s\n",data_spi_RW);
	ret = spiDataRW(data_spi_RW,SPI_DATA_SIZE);
	printf("Capteur n°: %d Validite: %d Distance: %dcm\n", data_spi_RW[0],data_spi_RW[1],data_spi_RW[2]);
	printf("Capteur n°: %d Validite: %d Distance: %dcm\n", data_spi_RW[3],data_spi_RW[4],data_spi_RW[5]);
	printf("Capteur n°: %d Validite: %d Distance: %dcm\n", data_spi_RW[6],data_spi_RW[7],data_spi_RW[8]);
	*/
	ret = spiDataRW(data_spi_RW,SPI_DATA_SIZE);
	//mesure_droit = (data_spi_RW[0]-'0')+(data_spi_RW[1]-'0')(data_spi_RW[2]-'0');
	//mesure_gauche = 
	printf("mesure 1 : %c%c%c%c%c%c\n",data_spi_RW[0],data_spi_RW[1],data_spi_RW[2],data_spi_RW[3],data_spi_RW[4],data_spi_RW[5]);
	printf("mesure 1 : %c%c%c%c%c%c\n",data_spi_RW[6],data_spi_RW[7],data_spi_RW[8],data_spi_RW[9],data_spi_RW[10],data_spi_RW[11]);
	return ret;
}
