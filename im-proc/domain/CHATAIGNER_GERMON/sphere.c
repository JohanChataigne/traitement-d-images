#include <stdio.h>
#include <math.h>
#include <bcl.h>
#include <string.h>
#include <stdlib.h>

#define M_PI 3.14159265358979323846

// degré de distorsion
#define K 3.0

void
process(char* ims, char* imd){

    pnm image = pnm_load(ims);
    int cols = pnm_get_width(image);
    int rows = pnm_get_height(image);

    int Ri = rows/2;
    int Rj = cols/2;

    // rayon du cercle auquel on se restreint
    int R_circle = (Ri + Rj)/4;

    // rayon maximum entre un point et le centre : diagonale de l'image
    double rmax = sqrt(pow(Ri, 2) + pow(Rj, 2));

    pnm new_image = pnm_new(cols, rows, PnmRawPpm);

    // transformation "fisheye" pour créer l'effet sphère
    for(int i = 0 ; i < rows ; i++) {
        for (int j = 0 ; j < cols ; j++) {
          int x = j - Rj;
          int y = i - Ri;

          // passage aux coordonnées polaires
          double r = sqrt(pow(x, 2) + pow(y, 2));
          double theta = atan2(y, x);

          double s = r + pow(r, 3) * (K / pow(rmax, 2));

          // retour aux coordonnées cartésiennes
          int u = s * cos(theta) + Rj;
          int v = s * sin(theta) + Ri;

          for (int c = 0 ; c < 3 ; c++) {
            if(u >= 0 && u < cols && v >= 0 && v <  rows) {
                // on n'affiche que les points qui sont à l'intérieur du cercle de rayon R_circle
                if(pow(R_circle, 2) > pow(j - Rj, 2) + pow(i - Ri, 2))
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
