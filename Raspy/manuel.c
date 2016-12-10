#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#include "manuel.h"
#include "kbhit.h"
#include "move_car.h"
#include "music.h"

void manuel(void)
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
	printf("Gps = G \n");
	printf("End Prog = e \n\n");
	gps gps_main;
	
	//BOUCLE PRINCIPALE
	while(1)
	{
		delay(250);
		if(kbhit())
		{
			char touche=getchar();
			switch(touche)
			{
				case 'o' : // Devant
					move_front();	
					break;
					
				case 'k' : // Gauche
					move_left();
					break;
					
				case 'l' : // Derriere
					move_back();
					break;
					
				case 'm' : // Droite
					move_right();
					break;
				case 65:    // key up 
					move_front();
					break;
			    	case 66:    // key down
					move_back();
				        break;
				case 67:    // key right
        				move_right();
					break;
				case 68:    // key left
					move_left();
					break;
				case 32:    // space	
				case 'i' : // Stop left right
					stop_left_right();
					break;
				case '\n' :
				case 'p' : // Stop front back
					stop_front_back();
					break;

				case 'e' : //Fin
					stop_front_back();
					stop_left_right();
					exit(1);
					break;

				case 'a': //Music voiture
					music();
					break;
				case 'w': //Captor
					captor();
					break;

				case 'G': //Captor
					gps_main.getPos();
					break;
	
				/*case 'x': // Cap et Position
					cap = get_cap(*p_magneto_calib_manuel);
					printf ("cap : %f\n", cap);
					printf ("Position X : %lu\n", p_coord_voiture_manuel->posX);
					printf ("Position Y : %lu\n", p_coord_voiture_manuel->posY);
					break;*/			
				default: printf("NULLL !!!\n");
			}// SWITCH
		}//KBHIT
	}//WHILE
}//FONCTION
