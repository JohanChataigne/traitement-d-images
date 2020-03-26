#include <stdlib.h>
#include <stdio.h>
#include <pnm.h>
#include <bcl.h>

void
process(int dx, int dy, char* ims_name, char* imd_name)
{
  // get given image
  pnm image = pnm_load(ims_name);

  if (image == NULL) {
    fprintf(stderr, "Error: couldn't load image\n");
    exit(1);
  }

  // get size of source image
  int image_cols = pnm_get_width(image);
  int image_rows = pnm_get_height(image);

  // create a new empty image
  pnm new_image = pnm_new(image_cols, image_rows, PnmRawPpm);

  // process move
  for (size_t i = 0; i < image_rows - dy; i++) {
    for (size_t j = 0; j < image_cols - dx; j++) {
      for (size_t k = 0 ; k < 3 ; k++) {

        // if the pixel (i,j) is in the "translated area", sets the channel k of the pixel (i,j) to 0
        if ((int) i <= dy && (int) j <= dx) {
          pnm_set_component(new_image, i, j, k, 0);
        }

        // sets the channel k of the pixel (i+dy, j+dx) with the value of the channel k of the pixel (i,j)
        pnm_set_component(new_image, i + dy, j + dx, k, pnm_get_component(image, i, j, k));
      }
    }
  }

  // save image in file
  pnm_save(new_image, PnmRawPpm, imd);

  // free structures
  pnm_free(image);
  pnm_free(new_image);
}

void
usage(char* s)
{
  fprintf(stderr,"%s <dx> <dy> <ims> <imd>\n",s);
  exit(EXIT_FAILURE);
}

#define PARAM 4
int
main(int argc, char* argv[])
{
  if(argc != PARAM+1)
    usage(argv[0]);

  int dx = atoi(argv[1]);
  int dy = atoi(argv[2]);

  process(dx, dy, argv[3], argv[4]);

  return EXIT_SUCCESS;
}
