#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>

void process (char * ims0, char * ims1, char * ims2, char * imd) {
  
  pnm image0 = pnm_load(ims0);
  pnm image1 = pnm_load(ims1);
  pnm image2 = pnm_load(ims2);

  if( (pnm_get_height(image0), pnm_get_height(image1)) != (pnm_get_height(image1), pnm_get_height(image2)) ) {
    fprintf(stderr, "Heights not matching\n");
    return;
  }

  if( (pnm_get_width(image0), pnm_get_width(image1)) != (pnm_get_width(image1), pnm_get_width(image2)) ) {
    fprintf(stderr, "Widths not matching\n");
    return;
  }

  pnm new_image = pnm_new(pnm_get_width(image0), pnm_get_height(image0), PnmRawPpm);

  unsigned short * channel0 = pnm_get_channel(image0, NULL, 0);
  unsigned short * channel1 = pnm_get_channel(image1, NULL, 1);
  unsigned short * channel2 = pnm_get_channel(image2, NULL, 2);

  pnm_set_channel(new_image, channel0, 0);
  pnm_set_channel(new_image, channel1, 1);
  pnm_set_channel(new_image, channel2, 2);

  pnm_save(new_image, PnmRawPpm, imd);

  pnm_free(image0);
  pnm_free(image1);
  pnm_free(image2);
  pnm_free(new_image);

  free(channel0);
  free(channel1);
  free(channel2);   
}

void usage (char *s) {

  fprintf(stderr,"Usage: %s %s", s, "<ims0> <ims1> <ims2> <imd>\n");
  fprintf(stderr, "Sources must have the same size...\n");
  exit(EXIT_FAILURE);

}

#define PARAM 4

int main(int argc, char *argv[]) {

  if (argc != PARAM+1) 
    usage(argv[0]);
  
  process(argv[1], argv[2], argv[3], argv[4]);

  return EXIT_SUCCESS;

}
