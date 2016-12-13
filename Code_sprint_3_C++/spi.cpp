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

float Spi::spiGetMesure1()
{
	return mesure1;
}

float Spi::spiGetMesure2()
{
	return mesure2;
}

int Spi::spiPrintRW(void)
{
	int ret;
	char car1,car2,car3,car4,car5;
	/*printf("------------------------\n");
	printf("Chaine a envoyer : %s\n",data_spi_RW);
	ret = spiDataRW(data_spi_RW,SPI_DATA_SIZE);
	printf("Capteur n°: %d Validite: %d Distance: %dcm\n", data_spi_RW[0],data_spi_RW[1],data_spi_RW[2]);
	printf("Capteur n°: %d Validite: %d Distance: %dcm\n", data_spi_RW[3],data_spi_RW[4],data_spi_RW[5]);
	printf("Capteur n°: %d Validite: %d Distance: %dcm\n", data_spi_RW[6],data_spi_RW[7],data_spi_RW[8]);
	*/
	ret = spiDataRW(data_spi_RW,SPI_DATA_SIZE);
	int i = 0;
	int j = 10;
	while(data_spi_RW[i] != '.' && i != 11)
		i++;
	while(data_spi_RW[j] != '.' && j != 21)
		j++;
	if(i == 1)
	{
		car1 =  data_spi_RW[0] - '0';
		car2 =  data_spi_RW[2] - '0';
		car3 =  data_spi_RW[3] - '0';
		car4 =  data_spi_RW[4] - '0';
		car5 =  data_spi_RW[5] - '0';
		mesure1 = (float)car1+(float)car2/10.0+(float)car3/100.0+(float)car4/1000.0+(float)car5/10000.0;
	}
	if(i == 2)
	{
		car1 =  data_spi_RW[0] - '0';
		car2 =  data_spi_RW[1] - '0';
		car3 =  data_spi_RW[3] - '0';
		car4 =  data_spi_RW[4] - '0';
		car5 =  data_spi_RW[5] - '0';
		mesure1 = (float)car1*10.0+(float)car2+(float)car3/10.0+(float)car4/100.0+(float)car5/1000.0;
	}
	if(i == 3)
	{
		car1 =  data_spi_RW[0] - '0';
		car2 =  data_spi_RW[1] - '0';
		car3 =  data_spi_RW[2] - '0';
		car4 =  data_spi_RW[4] - '0';
		car5 =  data_spi_RW[5] - '0';
		mesure1 = (float)car1*100.0+(float)car2*10.0+(float)car3+(float)car4/10.0+(float)car5/100.0;
	}

	if(j == 11)
	{
		car1 =  data_spi_RW[10] - '0';
		car2 =  data_spi_RW[12] - '0';
		car3 =  data_spi_RW[13] - '0';
		car4 =  data_spi_RW[14] - '0';
		car5 =  data_spi_RW[15] - '0';
		mesure2 = (float)car1+(float)car2/10.0+(float)car3/100.0+(float)car4/1000.0+(float)car5/10000.0;
	}
	if(j == 12)
	{
		car1 =  data_spi_RW[10] - '0';
		car2 =  data_spi_RW[11] - '0';
		car3 =  data_spi_RW[13] - '0';
		car4 =  data_spi_RW[14] - '0';
		car5 =  data_spi_RW[15] - '0';
		mesure2 = (float)car1*10.0+(float)car2+(float)car3/10.0+(float)car4/100.0+(float)car5/1000.0;
	}
	if(j == 13)
	{
		car1 =  data_spi_RW[10] - '0';
		car2 =  data_spi_RW[11] - '0';
		car3 =  data_spi_RW[12] - '0';
		car4 =  data_spi_RW[14] - '0';
		car5 =  data_spi_RW[15] - '0';
		mesure2 = (float)car1*100.0+(float)car2*10.0+(float)car3+(float)car4/10.0+(float)car5/100.0;
	}
	//printf("mesure 1 : %c%c%c%c%c%c\n",data_spi_RW[0],data_spi_RW[1],data_spi_RW[2],data_spi_RW[3],data_spi_RW[4],data_spi_RW[5]);
	//printf("mesure 2 : %c%c%c%c%c%c\n",data_spi_RW[10],data_spi_RW[11],data_spi_RW[12],data_spi_RW[13],data_spi_RW[14],data_spi_RW[15]);
	return ret;
}

void Spi::spiPrint(void)
{
	printf("Measure left = %fm\n",mesure1);
	printf("Mesure Right = %fm\n",mesure2);
	printf("DELTA MEASURE = %fcm\n",(mesure1-mesure2)*100.0);
	
}
