#ifndef MUSIC_H
#define MUSIC_H

#include <ao/ao.h>
#include <mpg123.h>

#include "Mediator.h"

class Music
{
public:
  //** SINGLETON
  static Music* instance();
  //** METHODS
  void *Music::thMusicHelper(void* context);
  void* Music::thMusic(void);

private:
  //** SINGLETON
	Music();
	Mediator* m_mediator;
	static Music* s_instance;

  //** ATTRIBUTES
  mpg123_handle *mh;
  unsigned char *buffer;
  size_t buffer_size;
  size_t done;
  int err;
  int etat_music;
  int cpt_music;
  char table_music[5][17];
  int driver;
  ao_device *dev;
  ao_sample_format format;
  int channels, encoding;
  long rate;
  int cpt_music_old;

  //** ERROR
	int result_code;
	//** THREAD
	pthread_t th_music;

};

#endif
