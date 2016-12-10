#ifndef MUSIC_H
#define MUSIC_H

class Music
{
private:
  mpg123_handle *mh;
  unsigned char *buffer;
  size_t buffer_size;
  size_t done;
  int err;
  int etat_music;
  int cpt_music;
  char table_music[4][17];
  int driver;
  ao_device *dev;

  ao_sample_format format;
  int channels, encoding;
  long rate;

public:
  Music();
  void lunchMusic(void);
};

#endif
