#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <bcl.h>
#include <string.h>

#define M_PI 3.14159265358979323846

void
process(char* dir, int angle, char* ims, char* imd){

    pnm image = pnm_load(ims);
    pnm new_image;
    int new_cols, new_rows;

    int cols = pnm_get_width(image);
    int rows = pnm_get_height(image);

    switch(dir[0]) {
        case 'h':

            new_cols = cols + rows * tan(abs(angle)); //width of the new image
            new_image = pnm_new(new_cols, rows, PnmRawPpm);

            /* iterate on the new image */
            for (size_t i = 0 ; i < (size_t) rows ; i++) {
                int j0 = 0; //cursor for culumns in the source image
                for (size_t j = 0 ; j < (size_t) new_cols ; j++) {
                    if ((j < i * tan(angle)) || (j > i * tan(angle) + cols)) { //check if the pixel is in one of the black triangles
                        for(int c = 0 ; c < 3; c++) {
                            pnm_set_component(new_image, i, j, c, 0);
                        }
                    } else {
                        for(int c = 0 ; c < 3; c++) {
                            pnm_set_component(new_image, i, j, c, pnm_get_component(image, i, j0, c));
                        }
                        j0++; //incremented only if we pick a pick a pixel in the source image
                    }
                }
            }

            break;
        case 'v':

            new_rows = rows + cols * tan(abs(angle)); //height of the new image
            new_image = pnm_new(cols, new_rows, PnmRawPpm);

            /* iterate on the new image */
            for (size_t j = 0 ; j < (size_t) cols ; j++) {
                int i0 = 0; //cursor for culumns in the source image
                for (size_t i = 0 ; i < (size_t) new_rows ; i++) {
                    if ((i < j * tan(angle)) || (i > j * tan(angle) + rows)) { //check if the pixel is in one of the black triangles
                        for(int c = 0 ; c < 3; c++) {
                            pnm_set_component(new_image, i, j, c, 0);
                        }
                    } else {
                        for(int c = 0 ; c < 3; c++) {
                            pnm_set_component(new_image, i, j, c, pnm_get_component(image, i0, j, c));
                        }
                        i0++; //incremented only if we pick a pick a pixel in the source image
                    }
                }
            }

            break;
        default:
            fprintf(stderr, "Error unknown direction\n");
            exit(1);
    }

    pnm_save(new_image, PnmRawPpm, imd);
    pnm_free(image);
    pnm_free(new_image);

}

static void usage(char* s){
  fprintf(stderr,"%s <dir>{h ,v} <angle> <ims> <imd>\n",s);
  exit(EXIT_FAILURE);
}

#define PARAM 4

int main(int argc, char* argv[]){

    if(argc != PARAM+1 || strlen(argv[1]) != 1)
        usage(argv[0]);

    process(argv[1], atoi(argv[2]) * M_PI / 180, argv[3], argv[4]);

    return EXIT_SUCCESS;
}
