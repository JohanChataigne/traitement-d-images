#include <stdlib.h>
#include <stdio.h>
#include <bcl.h>

void
process(int dx, int dy, char* ims_name, char* imd_name)
{
    pnm image = pnm_load(ims_name);

    if (image == NULL) {
        fprintf(stderr, "Error: couldn't load image\n");
        exit(1);
    }

    int cols = pnm_get_width(image);
    int rows = pnm_get_height(image);

    pnm new_image = pnm_new(cols, rows, PnmRawPpm);

    for (size_t i = 0 ; i < (size_t) rows ; i++) {
        for (size_t j = 0 ; j < (size_t) cols ; j++) {
            for(size_t c = 0 ; c < 3 ; c++) {
                pnm_set_component(new_image, (i + rows + dy) % rows , (j + cols + dx) % cols, c, pnm_get_component(image, i, j, c));
            }
        }
    }

    pnm_save(new_image, PnmRawPpm, imd_name);
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

  process(atoi(argv[1]), atoi(argv[2]), argv[3], argv[4]);

  return EXIT_SUCCESS;
}