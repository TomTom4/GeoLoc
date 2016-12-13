#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#include "manuel.h"
#include "kbhit.h"
#include "move_car.h"
#include "music.h"
#include "minmea.h"
#include "gps.h"
#include "carmodel.hpp"
#include "scenario.h"

Manuel::Manuel()
{
	touche = '0';
}
void Manuel::lunchManuel(void)
{
	//INSTRUCTIONS DE PILOTAGE
	printf("\n\n");
	printf("Utiliser les fleches directionnelles.  \n");
	printf("Front = o \n");
	printf("Left = k \n");
	printf("Back = l \n");
	printf("Right = m \n");
	printf("Captor = w \n");
	printf("Stop Left & Right = i ou espace \n");
	printf("Stop Front & back = p ou enter \n");
	printf("Music Voiture= a \n");
	printf("GPS = g \n");
	printf("Scenario Cap = t \n");
	printf("Scenario wheel Regulation = j \n");
	printf("End Prog = e \n\n");

	Spi spi_manuel;
	MoveCar move_car_manuel(&spi_manuel);
	Music music_manuel;
	Gps gps_manuel;
	Scenario scenario_manuel(&gps_manuel,&spi_manuel, &move_car_manuel);

	//BOUCLE PRINCIPALE
	while(1)
	{
		delay(250);
		//printf("delay\n");
		if(kbhit())
		{
			touche = getchar();
			//printf("touche %c\n",touche);
			//printf("tamp\n");
			switch(touche)
			{
				case 'o': // Devant
				case 65 :// key up
					//printf("touche = %c\n",touche);
					//printf("tamp\n");
					move_car_manuel.moveFront();
					break;

				case 'k': // Gauche
				case 68 :// key left
					move_car_manuel.moveLeft();
					break;

				case 'l': // Derriere
				case 66 :// key down
					move_car_manuel.moveBack();
					break;

				case 'm':// Droite
				case 67 :// key right
					move_car_manuel.moveRight();
					break;

				case 'i' : // Stop left right
				case 32:// space
					move_car_manuel.stopLeftRight();
					break;

				case 'p' : // Stop front back
				case '\n':
					move_car_manuel.stopFrontBack();
					break;

				case 'e' : //Fin
					move_car_manuel.stopFrontBack();
					move_car_manuel.stopLeftRight();
					exit(1);
					break;

				case 'a': //Music voiture
					music_manuel.lunchMusic();
					break;

				case 'w': //Captor
					move_car_manuel.captor();
					break;

				case 'g': // GPS
					printf("\n");
					gps_manuel.updatePos();
					break;
				
				case 't': // Scenario
					printf("\n");
					scenario_manuel.start();
					break;
				
				case 'f': // rien
					printf("\n");
					move_car_manuel.rien();
					break;
				case 'x': // rien
					printf("\n");
					move_car_manuel.center();
					break;
				case 'j': // rien
					for(int j = 0; i<500; j++)
					{
						printf("\n");
						delay(100);
						move_car_manuel.rien();
						spi_manuel.spiPrint();
					}
					move_car_manuel.stopFrontBack();
					break;

				/*case 'x': // Cap et Position
					cap = get_cap(*p_magneto_calib_manuel);
					printf ("cap : %f\n", cap);
					printf ("Position X : %lu\n", p_coord_voiture_manuel->posX);
					printf ("Position Y : %lu\n", p_coord_voiture_manuel->posY);
					break;*/
				//default: printf("NULLL !!!\n");
			}// SWITCH
		}//KBHIT
	}//WHILE
}//FONCTION

