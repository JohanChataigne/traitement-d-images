#include <stdio.h>
#include <math.h>
#include <bcl.h>
#include <string.h>

#define M_PI 3.14159265358979323846

void
process(int tx, int ax, int ty, int ay, char* ims, char* imd){

    pnm image = pnm_load(ims);
    int cols = pnm_get_width(image);
    int rows = pnm_get_height(image);
    pnm new_image1 = pnm_new(cols, rows, PnmRawPpm);
    pnm new_image2 = pnm_new(cols, rows, PnmRawPpm);

    double wx = 2*M_PI / tx;
    double wy = 2*M_PI / ty;

    for(int i = 0 ; i < rows ; i++) {
        double sin_i = ax * sin(wx * i)
        for (int j = 0 ; j < cols ; j++) {
                for(int c = 0 ; c < 3 ; c++) {
                  if(j + sin_i >= 0 && j + sin_i <= cols) {
                      pnm_set_component(new_image1, i, j + sin_i, c, pnm_get_component(image, i, j, c));
                  }
                }
        }
    }

    for(int j = 0 ; j < cols ; j++) {
        double sin_j = ay * sin(wy * j)
        for (int i = 0 ; i < rows ; i++) {
                for(int c = 0 ; c < 3 ; c++) {
                  if(i + sin_j >= 0 && i + sin_j <= cols) {
                      pnm_set_component(new_image2, i + sin_j, i, c, pnm_get_component(new_image1, i, j, c));
                  }
                }
        }
    }

    pnm_save(new_image2, PnmRawPpm, imd);
    pnm_free(image);
    pnm_free(new_image1);
    pnm_free(new_image2);

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
