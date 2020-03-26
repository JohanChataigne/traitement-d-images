#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>


int min_buffer(unsigned short * buffer, int buffer_size) {
  
  int min = 255;

  for(int i = 0 ; i < buffer_size ; i++) {
    if (buffer[i] < min) 
      min = buffer[i];
  }

  return min;
}

int max_buffer(unsigned short * buffer, int buffer_size) {
  
  int max = 0;

  for(int i = 0 ; i < buffer_size ; i++) {
    if (buffer[i] > max) 
      max = buffer[i];
  }

  return max;
}

int max_image(pnm image, int channel) {
  
  unsigned short * channel_buffer = pnm_get_channel(image, NULL, channel);
  
  int max_image = max_buffer(channel_buffer, pnm_get_height(image) * pnm_get_width(image));

  free(channel_buffer);

  return max_image;
}

int min_image(pnm image, int channel) {
  
unsigned short * channel_buffer = pnm_get_channel(image, NULL, channel);
  
  int min_image = min_buffer(channel_buffer, pnm_get_height(image) * pnm_get_width(image));

  free(channel_buffer);

  return min_image;

}
 
float normalize(pnm image, int i, int j, int min, int max, int min_image, int max_image, int channel) {

  unsigned short pixel_value = pnm_get_component(image, i, j, channel);
  
  return (1.0 * (max - min) / (max_image - min_image)) * pixel_value + (1.0 * (min * max_image - max * min_image) / (max_image - min_image));
}

void process (int min , int max, char * ims, char * imd) {
  
  pnm image = pnm_load(ims);

  int rows = pnm_get_height(image);
  int cols = pnm_get_width(image);

  pnm new_image = pnm_new(cols, rows, PnmRawPpm);

  for(int c = 0 ; c < 3 ; c++) {

    int Min = min_image(image, c);
    int Max = max_image(image, c);

    for(int i = 0 ; i < rows ; i++) {
      for(int j = 0 ; j < cols ; j++) {
	pnm_set_component(new_image, i, j, c, normalize(image, i, j, min, max, Min, Max, c));
      }
    }
    
  }

  pnm_save(new_image, PnmRawPpm, imd);

  pnm_free(image);
  pnm_free(new_image);
}

void usage (char *s) {

  fprintf(stderr,"Usage: %s %s", s, "<min> <max> <ims> <imd>\n");
  exit(EXIT_FAILURE);

}

#define PARAM 4

int main(int argc, char *argv[]) {

  if (argc != PARAM+1) 
    usage(argv[0]);
  
  int min = atoi(argv[1]);
  int max = atoi(argv[2]);

  process(min, max, argv[3], argv[4]);

  return EXIT_SUCCESS;

}
