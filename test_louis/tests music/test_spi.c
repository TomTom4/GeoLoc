
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

void init_spi()
{
	wiringPiSetup();
	// wiringPiSPISetup(int channel, int speed);
	//  	Param 1 : channel = 0 or 1
	//	Param 2 : Speed (Hz) =  500000 to 32000000
	if(wiringPiSPISetup(0,500000)<0)
		fprintf(stderr, "SPI Setup failed : %s\n",strerror (errno));


}
int main()
{

	char chaine_tx[30];
	char chaine_rx[30];
	char chaine_tampon[30] = "*** MESSAGE RASPI ***";
	//printf("\n Test SPI 0 a 500kHz\n");
	init_spi();
	while(1)
	{
		strcpy(chaine_tx,chaine_tampon);		
		printf("\n Chaine a envoyer : %s",chaine_tx);
		// wiringPiSPIDataRW(int channel, unsigned char *data, int len)
		// 	Param 1: channel = 0 or 1
		//	Param 2: pointeur sur chaine char de  data
		// 	Param 3: Taille de la chaine
		wiringPiSPIDataRW(0,(unsigned char*) chaine_tx,30);
		//wiringPiSPIDataRW2(0,(unsigned char*) chaine_tx,(unsigned char*) chaine_rx,30);
		printf("\n Chaine recu : %s", chaine_tx);
		sleep(1);
	}
}
