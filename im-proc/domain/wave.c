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
    pnm new_image = pnm_new(cols, rows, PnmRawPpm);

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
