#include <stdio.h>
#include <math.h>
#include <bcl.h>
#include <string.h>
#include <stdlib.h>

#define M_PI 3.14159265358979323846
#define K 5.0

void
process(char* ims, char* imd){

    pnm image = pnm_load(ims);
    int cols = pnm_get_width(image);
    int rows = pnm_get_height(image);

    int R = rows/2;

    int new_R = R * K / 2 - (K - 2) * R;

    //int new_cols = 2 * new_R;
    //int new_rows = 2 * new_R;

    pnm new_image = pnm_new(cols, rows, PnmRawPpm);

    double rmax = sqrt(2) * R;

    for(int i = 0 ; i < rows ; i++) {
        for (int j = 0 ; j < cols ; j++) {
          int x = j - R;
          int y = i - R;

          double r = sqrt(pow(x, 2) + pow(y, 2));
          double theta = atan2(y, x);
          double s = r + pow(r, 3) * (K / pow(rmax, 2));

          int u = s * cos(theta) + R;
          int v = s * sin(theta) + R;

          for (int c = 0 ; c < 3 ; c++) {
            if(u >= 0 && u < cols && v >= 0 && v <  rows) {
                if(pow(new_R, 2) > pow(j - R, 2) + pow(i - R, 2))
                    pnm_set_component(new_image, i, j, c, pnm_get_component(image, v, u, c));
            }
          }
        }
    }

    pnm_save(new_image, PnmRawPpm, imd);
    pnm_free(image);
    pnm_free(new_image);

}

static void usage(char* s){
  fprintf(stderr,"%s <ims> <imd>\n",s);
  exit(EXIT_FAILURE);
}

#define PARAM 2

int main(int argc, char* argv[]){

    if(argc != PARAM+1)
        usage(argv[0]);

    process(argv[1], argv[2]);

    return EXIT_SUCCESS;
}
