#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <bcl.h>
#include <string.h>

#define M_PI 3.14159265358979323846

void
process(int x0, int y0, double angle, char* ims, char* imd){

    pnm image = pnm_load(ims);
    int cols = pnm_get_width(image);
    int rows = pnm_get_height(image);
    pnm new_image = pnm_new(cols, rows, PnmRawPpm);

    //int angle_negative = (angle < 0);
    double cos_angle = cos(angle);
    double sin_angle = sin(angle);

    for(int i = 0 ; i < rows ; i++) {
        for (int j = 0 ; j < cols ; j++) {
                for(int c = 0 ; c < 3 ; c++) {

                    int x = j - x0; // in case center is not 0,0
                    int y = i - y0; // same
                    int x_prime = x * cos_angle - y * sin_angle + x0;
                    int y_prime = x * sin_angle + y * cos_angle + y0;

                    if( y_prime >= 0 && y_prime < rows && x_prime >= 0 && x_prime < cols ) { /
                        pnm_set_component(new_image, i, j, c, pnm_get_component(image, y_prime, x_prime, c));
                    }
                }
        }
    }

    pnm_save(new_image, PnmRawPpm, imd);
    pnm_free(image);
    pnm_free(new_image);

}

static void usage(char* s){
  fprintf(stderr,"%s <x> <y> <angle> <ims> <imd>\n",s);
  exit(EXIT_FAILURE);
}

#define PARAM 5

int main(int argc, char* argv[]){

    if(argc != PARAM+1)
        usage(argv[0]);

    process(atoi(argv[1]), atoi(argv[2]), atof(argv[3]) * M_PI / 180, argv[4], argv[5]);

    return EXIT_SUCCESS;
}
