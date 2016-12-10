#include <ao/ao.h>
#include <mpg123.h>

#include "music.h"
#include "kbhit.h"

#define BITS 8
#define MUSIC_OK 0
#define MUSIC_NEXT 1
#define MUSIC_STOP 2

Music::Music()
{
	/*strcpy(table_music[0],"music/music1.mp3");
	strcpy(table_music[0],"music/music2.mp3");
	strcpy(table_music[0],"music/music3.mp3");
	strcpy(table_music[0],"music/music4.mp3");
	etat_music = MUSIC_OK;
  	cpt_music = 0;*/
}

void Music::lunchMusic(void)
{
	/* initializations */
	/*ao_initialize();
	driver = ao_default_driver_id();
	mpg123_init();
	mh = mpg123_new(NULL, &err);
	buffer_size = mpg123_outblock(mh);
	buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

	do
	{
		if(etat_music == MUSIC_NEXT)
			cpt_music++;
		if(cpt_music == 4)
			cpt_music=0;
		//printf("cpt_music : %d",cpt_music);
		etat_music = MUSIC_OK;
    		mpg123_open(mh, table_music[cpt_music]);
		mpg123_getformat(mh, &rate, &channels, &encoding);
		format.bits = mpg123_encsize(encoding) * BITS;
		format.rate = rate;
		format.channels = channels;
		format.byte_format = AO_FMT_NATIVE;
		format.matrix = 0;
		dev = ao_open_live(driver, &format, NULL);

		while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK && etat_music == MUSIC_OK)
    		{
			ao_play(dev, (char*)buffer, done);
			if(kbhit())
			{
				char touche=getchar();
				switch(touche)
				{
					case 's' : // fin
						printf("Stop musique\n\n");
						etat_music = MUSIC_STOP;
						break;

					case 'z' : // music suivante
						printf("Musique suivante\n");
						etat_music = MUSIC_NEXT;
						break;
					//default:
				}// SWITCH

			}// IF
    }//WHILE
	}while(etat_music == MUSIC_NEXT);
	free(buffer);
	ao_close(dev);
	mpg123_close(mh);
	mpg123_delete(mh);
	mpg123_exit();
	ao_shutdown();*/
}// MUSIC
