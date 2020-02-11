#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>

void process (char * ims, char * imd) {
  
  pnm image = pnm_load(ims);

  unsigned short * channel0 = pnm_get_channel(image, NULL, 0);
  unsigned short * channel1 = pnm_get_channel(image, NULL, 1);
  unsigned short * channel2 = pnm_get_channel(image, NULL, 2);

  int cols = pnm_get_width(image);  
  int rows = pnm_get_height(image);

  unsigned short * mean_channel = malloc(sizeof(unsigned short) * rows * cols);

  for(int i = 0 ; i < rows * cols ; i++) {
    mean_channel[i] = (channel0[i] + channel1[i] + channel2[i]) / 3;
  }

  pnm new_image = pnm_new(cols, rows, PnmRawPpm);

  for(int c = 0 ; c < 3 ; c++) {
    pnm_set_channel(new_image, mean_channel, c);
  }

  pnm_save(new_image, PnmRawPpm, imd);

  free(channel0);
  free(channel1);
  free(channel2);
  free(mean_channel);

  pnm_free(image);
  pnm_free(new_image);
}

void usage (char *s) {

  fprintf(stderr,"Usage: %s %s", s, "<ims> <imd>\n");
  exit(EXIT_FAILURE);

}

#define PARAM 2

int main(int argc, char *argv[]) {

  if (argc != PARAM+1) 
    usage(argv[0]);
  
  process(argv[1], argv[2]);

  return EXIT_SUCCESS;

}
