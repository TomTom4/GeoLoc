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

using namespace std;


/*************************************/
/********PROGRAMME PRINCIPAL**********/
/*************************************/

int main (void)
{
  char choix;
  Manuel manuel_main;
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
			choix = getchar();
			printf("\n");
			switch(choix)
			{
				case 'C' : //VOIR FICHIER "manuel.h"
					manuel_main.lunchManuel();
					break;
				case 'I' : //VOIR FICHIER "interface.h"
					break;
				//default: printf("NULLL !!!\n");
			}// SWITCH
		}// IF
	}// WHILE
 return (0);
}// MAIN
