#include <stdlib.h>
#include <stdio.h>
#include <bcl.h>
#include <string.h>

pnm
flip (char dir, pnm image) {

    pnm copy = pnm_dup(image);

    int cols = pnm_get_width(image);
    int rows = pnm_get_height(image);

    switch (dir) {
        case 'h':
            for (size_t i = 0 ; i < (size_t) rows ; i++) {
                for (size_t j = 0 ; j < (size_t) cols ; j++) {
                    for(size_t c = 0 ; c < 3 ; c++) {
                        pnm_set_component(image, i, (cols - 1 - j), c, pnm_get_component(copy, i, j, c));
                    }
                }
            }
            break;
        case 'v':
            for (size_t i = 0 ; i < (size_t) rows ; i++) {
                for (size_t j = 0 ; j < (size_t) cols ; j++) {
                    for(size_t c = 0 ; c < 3 ; c++) {
                        pnm_set_component(image, (rows - 1 - i), j, c, pnm_get_component(copy, i, j, c));
                    }
                }
            }
            break;
        case 't':
            image = pnm_new(rows, cols, PnmRawPpm);
            for (size_t i = 0 ; i < (size_t) rows ; i++) {
                for (size_t j = 0 ; j < (size_t) cols ; j++) {
                    for(size_t c = 0 ; c < 3 ; c++) {
                        pnm_set_component(image, cols - 1 - j, rows - 1 - i, c, pnm_get_component(copy, i, j, c));
                    }
                }
            }
            break;
        default:
            fprintf(stderr, "Error invalid direction\n");
            exit(1);
            break;
    }

    pnm_free(copy);
    return image;
}


void
process(char* dirs, char* ims_name, char* imd_name)
{
    pnm image = pnm_load(ims_name);

    if (image == NULL) {
        fprintf(stderr, "Error couldn't load image\n");
        exit(1);
    }

    for (size_t i = 0 ; i < (size_t) strlen(dirs) ; i++) {
        image = flip(dirs[i], image);
    }

    pnm_save(image, PnmRawPpm, imd_name);
    pnm_free(image);
}


void
usage(char* s)
{
  fprintf(stderr,"%s <dir>{h, t, v}* <ims> <imd>\n",s);
  exit(EXIT_FAILURE);
}

#define PARAM 3
int
main(int argc, char* argv[])
{
  if(argc != PARAM+1)
    usage(argv[0]);

  process(argv[1], argv[2], argv[3]);

  return EXIT_SUCCESS;
}