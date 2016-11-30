#include <ao/ao.h>
#include <mpg123.h>

#include "music.h"
#include "kbhit.h"

#define BITS 8
#define MUSIC_OK 0
#define MUSIC_NEXT 1
#define MUSIC_STOP 2

void music(void)
{
	mpg123_handle *mh;
    	unsigned char *buffer;
    	size_t buffer_size;
	size_t done;
	int err;
	int etat_music = MUSIC_OK;
	int cpt_music = 0;
	char table_music[4][17] = {"music/music1.mp3","music/music2.mp3","music/music3.mp3","music/music4.mp3"};
	
	int driver;
	ao_device *dev;
	
	ao_sample_format format;
	int channels, encoding;
	long rate;
	
	/* initializations */
	ao_initialize();
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
		/* open the file and get the decoding format */
    		mpg123_open(mh, table_music[cpt_music]);
		mpg123_getformat(mh, &rate, &channels, &encoding);
	
		/* set the output format and open the output device */
		format.bits = mpg123_encsize(encoding) * BITS;
		format.rate = rate;
		format.channels = channels;
		format.byte_format = AO_FMT_NATIVE;
		format.matrix = 0;
		dev = ao_open_live(driver, &format, NULL);
	
		/* decode and play */
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
    	/* clean up */
    	free(buffer);
    	ao_close(dev);
    	mpg123_close(mh);
    	mpg123_delete(mh);
    	mpg123_exit();
    	ao_shutdown();
}// MUSIC