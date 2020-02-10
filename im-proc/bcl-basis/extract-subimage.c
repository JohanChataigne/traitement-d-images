#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>

void process (size_t i, size_t j, size_t rows, size_t cols, char * ims, char * imd) {

  // get given image
  pnm image = pnm_load(ims);
  
  if (image == NULL) {
    fprintf(stderr, "Error: couldn't load image\n");
    exit(1);
  }

  // create a new empty image
  pnm new_image = pnm_new(rows, cols, PnmRawPpm);
  
  // get both images buffers
  unsigned short * old_data = pnm_get_image(image);
  unsigned short * new_data = pnm_get_image(new_image);

  int i0 = pnm_offset(image, i, j);

  for (size_t k = i0 ; k < (i+rows)*(j+cols)*3 ; k++) {
 
    *new_data++ = old_data[k];
      
  }

  // save image in file
  pnm_save(new_image, PnmRawPpm, imd);

  // free structures
  pnm_free(image);
  pnm_free(new_image);

}

void usage (char *s) {

  fprintf(stderr,"Usage: %s %s", s, "<i> <j> <rows> <cols> <ims> <imd>\n");
  exit(EXIT_FAILURE);

}

#define PARAM 6

int main(int argc, char *argv[]) {

  if (argc != PARAM+1) 
    usage(argv[0]);
  
  size_t i = atoi(argv[1]);
  size_t j = atoi(argv[2]);
  size_t rows = atoi(argv[3]);
  size_t cols = atoi(argv[4]);

  process(i, j, rows, cols, argv[5], argv[6]);

  return EXIT_SUCCESS;

}
