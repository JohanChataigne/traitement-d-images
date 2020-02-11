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
  pnm new_image = pnm_new(cols, rows, PnmRawPpm);
  
    // get size of source image
  int image_cols = pnm_get_width(image);
  int image_rows = pnm_get_height(image);

  for (size_t i0 = i ; i0 < rows + i ; i0++) {

    size_t i1 = i0 - i;

    for (size_t j0 = j ; j0 < cols + j ; j0++) {
      
      size_t j1 = j0 - j;

      for (size_t k = 0 ; k < 3 ; k++) {
  
	if ((int) i0 < image_rows && (int) j0 < image_cols) { // check if the actual pixel is in the source image frame
	  pnm_set_component(new_image, i1, j1, k, pnm_get_component(image, i0, j0, k)); // copy the pixel value form source to destination
	} 
	else
	  pnm_set_component(new_image, i1, j1, k, pnm_maxval); // set to white if not in frame

      }
    }
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
