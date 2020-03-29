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
    pnm new_image = pnm_new(cols, rows, PnmRawPpm);
    double rmax = sqrt(pow(cols,2) + pow(rows,2))/2;

    for(int i = 0 ; i < rows ; i++) {
        for (int j = 0 ; j < cols ; j++) {
          int x = j - cols/2;
          int y = i - rows/2;

          double r = sqrt(pow(x, 2) + pow(y, 2));
          double theta = atan2(y, x);
          double s = r + pow(r, 3) * (K / pow(rmax, 2));

          int u = s * cos(theta) + cols/2;
          int v = s * sin(theta) + rows/2;

          for (int c = 0 ; c < 3 ; c++) {
            if(u >= 0 && u < cols && v >= 0 && v <  rows) {
                if(pow(cols/3.5, 2) >= pow(x , 2) + pow(y , 2))
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
