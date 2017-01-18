#include <ao/ao.h>
#include <mpg123.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


#include "Mediator.h"
#include "music.h"

#define BITS 8
#define MUSIC_OK 0
#define MUSIC_NEXT 1
#define MUSIC_STOP 2

Music* Music::s_instance = 0;

Music* Music::instance()
{
	if(!Music::s_instance)
		Music::s_instance = new Music();
		Music::s_instance->m_mediator = Mediator::instance();
	return Music::s_instance;
}

Music::Music()
{
	cout << " constructeur music " << endl;
	strcpy(table_music[0],"music/music1.mp3");
	strcpy(table_music[1],"music/music1.mp3");
	strcpy(table_music[2],"music/music2.mp3");
	strcpy(table_music[3],"music/music3.mp3");
	strcpy(table_music[4],"music/music4.mp3");
	cpt_music_old = 0;
	/* initializations */
	ao_initialize();
	driver = ao_default_driver_id();
	mpg123_init();
	mh = mpg123_new(NULL, &err);
	buffer_size = mpg123_outblock(mh);
	buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));
	//** Create Thread
	result_code = pthread_create(&th_music,NULL,thMusicHelper,this);
	if(result_code == 0)
	cout << "Creation Thread MUSIC - Ok" << endl;
}

void* Music::thMusic(void)
{
	while(1)
	{
		cout << " th music " << endl;
		if(MPG123_OK == mpg123_open(mh, table_music[m_mediator->getCptMusic()]));
		{
			cout << " mpg123 ok " << endl;	
			mpg123_getformat(mh, &rate, &channels, &encoding);
			format.bits = mpg123_encsize(encoding) * BITS;
			format.rate = rate;
			format.channels = channels;
			format.byte_format = AO_FMT_NATIVE;
			format.matrix = 0;
			dev = ao_open_live(driver, &format, NULL);
			while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK && m_mediator->getCptMusic() == cpt_music_old)
	    {
				ao_play(dev, (char*)buffer, done);
				usleep(1000);
	    }//WHILE
			cpt_music_old = m_mediator->getCptMusic();
		}
	}
	free(buffer);
	ao_close(dev);
	mpg123_close(mh);
	mpg123_delete(mh);
	mpg123_exit();
	ao_shutdown();
}

void* Music::thMusicHelper(void* context)
{
	return((Music*)context)->Music::thMusic();
}
