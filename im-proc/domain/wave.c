#include <stdio.h>
#include <math.h>
#include <bcl.h>
#include <string.h>
#include <stdlib.h>

#define M_PI 3.14159265358979323846

void
process(int tx, int ax, int ty, int ay, char* ims, char* imd){

    pnm image = pnm_load(ims);
    int cols = pnm_get_width(image);
    int rows = pnm_get_height(image);
    pnm new_image = pnm_new(cols, rows, PnmRawPpm);

    double wx = 2*M_PI / tx;
    double wy = 2*M_PI / ty;

    for(int i = 0 ; i < rows ; i++) {
        double sin_i = ax * cos(wx * i + M_PI/2);
        for (int j = 0 ; j < cols ; j++) {
            double sin_j = ay * cos(wy * j + M_PI/2);
                for(int c = 0 ; c < 3 ; c++) {
                  if(j - sin_i >= 0 && j - sin_i < cols && i - sin_j >= 0 && i - sin_j < cols) {
                      pnm_set_component(new_image, i, j, c, pnm_get_component(image, i - sin_j, j - sin_i, c));
                  }
                }
        }
    }

    pnm_save(new_image, PnmRawPpm, imd);
    pnm_free(image);
    pnm_free(new_image);

}

static void usage(char* s){
  fprintf(stderr,"%s <tx> <ax> <ty> <ay> <ims> <imd>\n",s);
  exit(EXIT_FAILURE);
}

#define PARAM 6

int main(int argc, char* argv[]){

    if(argc != PARAM+1)
        usage(argv[0]);

    process(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5], argv[6]);

    return EXIT_SUCCESS;
}
