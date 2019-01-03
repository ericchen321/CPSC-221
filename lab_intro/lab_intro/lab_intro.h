#ifndef LAB_INTRO_H
#define LAB_INTRO_H

#include "cs221util/PNG.h"
using namespace cs221util;

PNG grayscale(PNG image);  
PNG createSpotlight(PNG image, int centerX, int centerY);
PNG ubcify(PNG image);
PNG watermark(PNG firstImage, PNG secondImage);

#endif
