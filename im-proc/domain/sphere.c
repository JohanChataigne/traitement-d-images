#include <stdio.h>
#include <math.h>
#include <bcl.h>
#include <string.h>
#include <stdlib.h>

#define M_PI 3.14159265358979323846
#define K 3

void
process(char* ims, char* imd){

    pnm image = pnm_load(ims);
    int cols = pnm_get_width(image);
    int rows = pnm_get_height(image);
    pnm new_image = pnm_new(cols, rows, PnmRawPpm);

    for(int i = 0 ; i < rows ; i++) {
        double phi = i * 1.0 / rows * M_PI * 2;
        for (int j = 0 ; j < cols ; j++) {
            double theta = j * 1.0 / cols * M_PI * 2;
            double u = (1 - cos(phi)) * cos(theta);
            double v = (1 - cos(phi)) * sin(theta);
            int x = cols / 2 + (u + 1) * sqrt(pow(u, 2) + pow(v, 2));
            int y = rows / 2 + (v + 1) * sqrt(pow(u, 2) + pow(v, 2));
            for (int c = 0 ; c < 3 ; c++) {
                    pnm_set_component(new_image, i, j, c, pnm_get_component(image, y, x, c));
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
