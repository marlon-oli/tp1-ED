#ifndef IMAGE_H
#define IMAGE_H

typedef struct image Image;

/**
* Creates a new image.
*
* @param rows The number of rows (height) of the image.
3
* @param cols The number of columns (width) of the image.
* @param type The PPM type ("P2" for grayscale or "P3" for color).
* @return A pointer to the newly created image.
*/
Image* create(int rows, int cols, char type[]);

/**
* Loads an image from a PPM file.
*
* @param filename The name of the PPM file to load.
* @return A pointer to the loaded image.
*/
Image* load_from_ppm(const char* filename);

/**
* Writes an image to a PPM file.
*
* @param image The image to write to the file.
* @param filename The name of the PPM file to write.
*/
void write_to_ppm(Image* image, const char* filename);

/**
* Converts an RGB image to grayscale.
*
* @param image_rgb The input RGB image to convert.
* @param image_gray The output grayscale image where the result is
stored.
*/
void rgb_to_gray(Image* image_rgb, Image* image_gray);

//add
//free allocated memory
void free_image(Image* image);

//get the rows of an image
int get_rows(Image* image);

//get the cols of an image
int get_cols(Image* image);
//endofadd

#endif