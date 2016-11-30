// INCLUSION DES BIB DE BASE
#include <stdio.h> // getchar - printf

//INCLUSION DES BIB WIRINGPI
// Test com
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <wiringPiI2C.h>
#include <ao/ao.h>
#include <mpg123.h>

//INCLUSION DES FICHIERS HEADERS
#include "kbhit.h"
#include "spi.h"
#include "move_car.h"
#include "manuel.h"

//DECLARATION DES VARIABLES GLOBALES
//const int SPI_DATA_SIZE = 5+1;

const int STOP_ALL = 0;
const int STOP_FRONT_BACK = 1;
const int STOP_LEFT_RIGHT = 2;
const int MOVE_FRONT = 3;
const int MOVE_BACK = 4;
const int MOVE_LEFT = 5;
const int MOVE_RIGHT = 6;
const int CAPTOR = 7;

char table_spi[10][10/*SPI_DATA_SIZE*/] = {"00000", "11111","22222","33333","44444","55555","66666","77777","88888"};

char data_spi_RW[10/*SPI_DATA_SIZE*/];
char chaine_tampon[10/*SPI_DATA_SIZE*/] = "12345";

char choix;


using namespace std;

/*************************************/
/********PROGRAMME PRINCIPAL**********/
/*************************************/

int main (void)
{
	//PRESENTATION
printf("\t\n\n\n");   	                                                                   
printf("\t\t    _/    _/  _/      _/  _/_/_/    _/_/_/  _/    _/  _/_/_/_/_/\n");   
printf("\t\t   _/  _/    _/_/    _/    _/    _/        _/    _/      _/     \n");
printf("\t\t  _/_/      _/  _/  _/    _/    _/  _/_/  _/_/_/_/      _/      \n");   
printf("\t\t _/  _/    _/    _/_/    _/    _/    _/  _/    _/      _/       \n");   
printf("\t\t_/    _/  _/      _/  _/_/_/    _/_/_/  _/    _/      _/        \n\n\n");   
                                                                   
        printf("\t\t\t/////////////////////////////////////////////\n");
	printf("\t\t\t// Programme Principal Geoloc Raspberry Pi //\n");
	printf("\t\t\t// Bibilotheque : wiringPi		   //\n");
	printf("\t\t\t// Version: 1.0				   //\n");
	printf("\t\t\t// Auteur : Knight Team			   //\n");
	printf("\t\t\t/////////////////////////////////////////////\n\n");

	//PARAMETRAGE BIB WIRINGPI	
	wiringPiSetup ();
	
	//PARAMETRAGE SPI
	if(wiringPiSPISetup(0,1000000)<0)
		//fprintf("SPI Setup failed : %s\n",strerror(errno));
	
	// CHOIX CLAVIER OU INTERFACE GRAPHIQUE
	printf("\n");
	printf("Pour utiliser le clavier tapez : C.\n");
	printf("Pour lancer l'interface graphique tapez : I.\n");
	printf("Choix: ");
		
	while(1)
	{
		delay(500);
		if(kbhit())
		{	
			choix=getchar();
			printf("\n");
			switch(choix)
			{
				case 'C' : //VOIR FICHIER "manuel.h"
					manuel();
					break;
				case 'I' : //VOIR FICHIER "interface.h"
					break;
				default: printf("NULLL !!!\n");
			}// SWITCH
		}// IF
	}// WHILE
 return (0);
}// MAIN
