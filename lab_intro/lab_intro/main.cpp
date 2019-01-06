/**
 * @file main.cpp
 * A simple C++ program that manipulates an image.
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#include "lab_intro.h"
#include "cs221util/PNG.h"

int main() {
  cs221util::PNG png, png2, result;

  png.readFromFile("rosegarden.png");
  result = grayscale(png);
  result.writeToFile("out-grayscale.png");
  
  result = createSpotlight(png, 300, 300);
  result.writeToFile("out-spotlight.png");

  result = ubcify(png);
  result.writeToFile("out-ubcify.png");

  png2.readFromFile("overlay.png");
  result = watermark(png, png2);
  result.writeToFile("out-watermark.png");
  
  return 0;
}
