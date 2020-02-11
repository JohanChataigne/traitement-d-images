#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>

void process (int channel, char * ims, char * imd) {
  
  pnm image = pnm_load(ims);

  unsigned short * channel_buffer = pnm_get_channel(image, NULL, channel);

  int rows = pnm_get_height(image);
  int cols = pnm_get_width(image);

  pnm new_image = pnm_new(cols, rows, PnmRawPpm);

  for (int c = 0 ; c <3 ; c++) {
    pnm_set_channel(new_image, channel_buffer, c);
  }

  pnm_save(new_image, PnmRawPpm, imd);

  pnm_free(image);
  pnm_free(new_image);
  free(channel_buffer);
}

void usage (char *s) {

  fprintf(stderr,"Usage: %s %s", s, "<num> <ims> <imd>\n");
  exit(EXIT_FAILURE);

}

#define PARAM 3

int main(int argc, char *argv[]) {

  if (argc != PARAM+1) 
    usage(argv[0]);
  
  int channel = atoi(argv[1]);

  process(channel, argv[2], argv[3]);

  return EXIT_SUCCESS;

}
