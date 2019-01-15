
#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <iostream>
#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
using namespace std;
using namespace cs221util;

class Block{

public:
   /* From im, grabs the vertical strip of
      pixels whose upper left corner is at position 
      (column,0), and whose width is width.
   */
   void build(PNG & im, int column, int width);

   /* Draws the current block at position
      (column,0) in im.
   */
   void render(PNG & im, int column) const ;

   /* This function changes the saturation of 
      every pixel in the block to 0, which
      removes the color, leaving grey.
   */
   void greyscale();

   /*  Returns the width of the current block
   */
   int width() const ;

   /* Returns the height of the current block.
   */
   int height() const ;

private:

   vector< vector < HSLAPixel > > data;

};
#endif
