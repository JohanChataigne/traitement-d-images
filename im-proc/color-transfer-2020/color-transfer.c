/**
 * @file color-transfert
 * @brief transfert color from source image to target image.
 *        Method from Reinhard et al. : 
 *        Erik Reinhard, Michael Ashikhmin, Bruce Gooch and Peter Shirley, 
 *        'Color Transfer between Images', IEEE CGA special issue on 
 *        Applied Perception, Vol 21, No 5, pp 34-41, September - October 2001
 */

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <bcl.h>

#define D 3

float RGB2LMS[D][D] = {
  {0.3811, 0.5783, 0.0402}, 
  {0.1967, 0.7244, 0.0782},  
  {0.0241, 0.1288, 0.8444}
};

float LMS2lab[D][D] = {
  {0.5773, 0.5773, 0.5773},
  {0.4082, 0.4082, -0.8165},
  {0.7071, -0.7071, 0}
};

float lab2LMS[D][D] = {
  {0.5773, 0.4082, 0.7071},
  {0.5773, 0.4082, -0.7071},
  {0.5773, -1.4142, 0}
};

float LMS2RGB[D][D] = {
  {4.4679, -3.5873, 0.1193},
  {-1.2186, 2.3809, -0.1624},
  {0.0497, -0.2439, 1.2045}
};

/* compute RGB to LMS transform for a pixel in a given channel in LMS space */
float
rgb_to_lms_val(pnm image, int row, int col, pnmChannel c) {
    return RGB2LMS[c][0] * pnm_get_component(image, row, col, 0)
            + RGB2LMS[c][1] * pnm_get_component(image, row, col, 1)
            + RGB2LMS[c][2] * pnm_get_component(image, row, col, 2);
}

/* compute LMS to lab transform for a pixel in a given channel in lab space */
float
lms_to_lab_val(float * image, int width, int row, int col, pnmChannel c) {
    return LMS2lab[c][0] * image[3*(row * width + col)]
            + LMS2lab[c][1] * image[3*(row * width + col) + 1]
            + LMS2lab[c][2] * image[3*(row * width + col) + 2];
}

/* compute lab to LMS transform for a pixel in a given channel in LMS space */
float
lab_to_lms_val(float * image, int width, int row, int col, pnmChannel c) {
    return lab2LMS[c][0] * image[3*(row * width + col)]
            + lab2LMS[c][1] * image[3*(row * width + col) + 1]
            + lab2LMS[c][2] * image[3*(row * width + col) + 2];
}

/* compute LMS to RGB transform for a pixel in a given channel in RGB space */
float
lms_to_rgb_val(float * image, int width, int row, int col, pnmChannel c) {
    return LMS2RGB[c][0] * image[3*(row * width + col)]
            + LMS2RGB[c][1] * image[3*(row * width + col) + 1]
            + LMS2RGB[c][2] * image[3*(row * width + col) + 2];
}

/* Compute RGB to LMS transform for a whole given image and return the new image in LMS space */
float * rgb_to_lms_transform(pnm RGB_image) {

    int rows = pnm_get_height(RGB_image);
    int cols = pnm_get_width(RGB_image);
    //pnm LMS_image = pnm_new(cols, rows, PnmRawPpm);
    float * LMS_image = malloc(rows * cols * 3 * sizeof(float));

    for(int i = 0 ; i < rows ; i++) {
        for (int j = 0 ; j < cols ; j++) {
            for(int c = 0 ; c < 3 ; c++) {
                /* Fill LMS image pixels computed with transform matrix and apply log */
                //pnm_set_component(LMS_image, i, j, c, log10f(rgb_to_lms_val(RGB_image, i, j, c)));
                LMS_image[3*(i * cols + j) + c] = log10f(rgb_to_lms_val(RGB_image, i, j, c));
            }
        }
    }

    return LMS_image;
}

/* Compute LMS to lab transform for a whole given image and return the new image in lab space */
float * lms_to_lab_transform(float * LMS_image, int rows, int cols) {

    //int rows = pnm_get_height(LMS_image);
    //int cols = pnm_get_width(LMS_image);
    //pnm lab_image = pnm_new(cols, rows, PnmRawPpm);
    float * lab_image = malloc(rows * cols * 3 * sizeof(float));

    for(int i = 0 ; i < rows ; i++) {
        for (int j = 0 ; j < cols ; j++) {
            for(int c = 0 ; c < 3 ; c++) {
                /* Fill lab image pixels computed with transform matrix */
                //pnm_set_component(lab_image, i, j, c, lms_to_lab_val(LMS_image, i, j, c));
                lab_image[3*(i * cols + j) + c] = lms_to_lab_val(LMS_image, cols, i, j, c);
            }
        }
    }

    return lab_image;
}

/* Compute lab to LMS transform for a whole given image and return the new image in LMS space */
float * lab_to_lms_transform(float * lab_image, int rows, int cols) {

    //int rows = pnm_get_height(lab_image);
    //int cols = pnm_get_width(lab_image);
    //pnm LMS_image = pnm_new(cols, rows, PnmRawPpm);
	float * LMS_image = malloc(rows * cols * 3 * sizeof(float));

    for(int i = 0 ; i < rows ; i++) {
        for (int j = 0 ; j < cols ; j++) {
            for(int c = 0 ; c < 3 ; c++) {
                /* Fill LMS image pixels computed with transform matrix */
                //pnm_set_component(LMS_image, i, j, c, powf(10, lab_to_lms_val(lab_image, i, j, c)));
                LMS_image[3*(i * cols + j) + c] = powf(10, lab_to_lms_val(lab_image, cols, i, j, c));
            }
        }
    }

    return LMS_image;
}

/* Compute LMS to RGB transform for a whole given image and return the new image in RGB space */
pnm lms_to_rgb_transform(float * LMS_image, int rows, int cols) {

    //int rows = pnm_get_height(LMS_image);
    //int cols = pnm_get_width(LMS_image);
    pnm RGB_image = pnm_new(cols, rows, PnmRawPpm);

    for(int i = 0 ; i < rows ; i++) {
        for (int j = 0 ; j < cols ; j++) {
            for(int c = 0 ; c < 3 ; c++) {
                /* Fill LMS image pixels computed with transform matrix */
                pnm_set_component(RGB_image, i, j, c, lms_to_rgb_val(LMS_image, cols, i, j, c));
            }
        }
    }

    return RGB_image;
}

float axis_mean(float * image, int rows, int cols, pnmChannel c) {

    //int rows = pnm_get_height(image);
    //int cols = pnm_get_width(image);
    int size = rows * cols * 3;

    //unsigned short * buffer = pnm_get_channel(image, NULL, c);
    float mean = 0;

    for (int i = c ; i < size ; i += 3) {
        mean += image[i];
    }

	//free(buffer);

    return mean / size;
}

float axis_standard_deviation(float * image, int rows, int cols, pnmChannel c, float mean) {

    //int rows = pnm_get_height(image);
    //int cols = pnm_get_width(image);
    int size = rows * cols * 3;

    //unsigned short * buffer = pnm_get_channel(image, NULL, c);
    float sum = 0;

    for (int i = c ; i < size ; i += 3) {
        sum += powf(image[i] - mean, 2);
    }

    //free(buffer);

    return sqrt(sum / (float)(size - 1));
}

void
process(char *ims, char *imt, char* imd){

    /* load both source and target image into pnm objects */
    pnm image_source = pnm_load(ims);
    pnm image_target = pnm_load(imt);

    int rows_source = pnm_get_height(image_source);
    int cols_source = pnm_get_width(image_source);
    int rows_target = pnm_get_height(image_target);
    int cols_target = pnm_get_width(image_target);


    /* RGB to LMS transformation for both images */
    float * LMS_source = rgb_to_lms_transform(image_source);
    float * LMS_target = rgb_to_lms_transform(image_target);

    /* Then transform again to get lab images */
    float * lab_source = lms_to_lab_transform(LMS_source, rows_source, cols_source);
    float * lab_target = lms_to_lab_transform(LMS_target, rows_target, cols_target);

    /* Compute mean + standard deviation for each axis of each image */

    float mean_source[D] = {
                             axis_mean(lab_source, rows_source, cols_source, 0),
                             axis_mean(lab_source, rows_source, cols_source, 1),
                             axis_mean(lab_source, rows_source, cols_source, 2)
                           };

    float mean_target[D] = {
                               axis_mean(lab_target, rows_target, cols_target, 0),
                               axis_mean(lab_target, rows_target, cols_target, 1),
                               axis_mean(lab_target, rows_target, cols_target, 2)
                             };

    float sigma_source[D] = {
                             axis_standard_deviation(lab_source, rows_source, cols_source, 0, mean_source[0]),
                             axis_standard_deviation(lab_source, rows_source, cols_source, 1, mean_source[1]),
                             axis_standard_deviation(lab_source, rows_source, cols_source, 2, mean_source[2])
                            };

    float sigma_target[D] = {
                                axis_standard_deviation(lab_target, rows_target, cols_target, 0, mean_target[0]),
                                axis_standard_deviation(lab_target, rows_target, cols_target, 1, mean_target[1]),
                                axis_standard_deviation(lab_target, rows_target, cols_target, 2, mean_target[2])
                              };

    /* Color processing */

    for(int i = 0 ; i < rows_target ; i++) {
        for (int j = 0 ; j < cols_target ; j++) {
            for(int c = 0 ; c < 3 ; c++) {
                /* process color of the pixel */
                float new_value = (sigma_target[c] / sigma_source[c]) * (lab_target[3*(i * cols_target + j) + c] - mean_target[c]) + mean_source[c];
                lab_target[3*(i * cols_target + j) + c] = new_value;
            }
        }
    }

    /* Convert back to LMS */
    float * LMS_new_image = lab_to_lms_transform(lab_target, rows_target, cols_target);

    /* Convert back to RGB */
    pnm new_image = lms_to_rgb_transform(LMS_new_image, rows_target, cols_target);

    /* save result on disk */
    pnm_save(new_image, PnmRawPpm, imd);

    /*pnm_save(LMS_source, PnmRawPpm, "_lms_source.ppm");
    pnm_save(LMS_target, PnmRawPpm, "_lms_target.ppm");
    pnm_save(lab_source, PnmRawPpm, "_lab_source.ppm");
    pnm_save(lab_target, PnmRawPpm, "_lab_target.ppm");
    pnm_save(LMS_new_image, PnmRawPpm, "_lms_new_image.ppm");*/


    /* Free all pnm images created */
    pnm_free(image_source);
    pnm_free(image_target);
    free(LMS_source);
    free(LMS_target);
    free(lab_source);
    free(lab_target);
    free(LMS_new_image);
    pnm_free(new_image);

}

void
usage (char *s){
  fprintf(stderr, "Usage: %s <ims> <imt> <imd> \n", s);
  exit(EXIT_FAILURE);
}


#define PARAM 3
int
main(int argc, char *argv[]){
  if (argc != PARAM+1) usage(argv[0]);
  process(argv[1], argv[2], argv[3]);
  return EXIT_SUCCESS;
}
