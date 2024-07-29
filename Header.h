#pragma once

#include <iostream>
#include <vector>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <float.h>
#include <chrono>


typedef struct
{
  unsigned char red;
  unsigned char green;
  unsigned char blue;

}Pixel;

typedef struct
{
  char file_name[100];
  unsigned int height;
  unsigned int width;
  unsigned int size;
  Pixel** pixels;

}RGB_Image;

void two_images(void);
int load_image(RGB_Image*);
int save_image(RGB_Image);
void free_pixels(RGB_Image);


