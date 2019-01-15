#include "block.h"
#include "cs221util/PNG.h"

/* From im, grabs the vertical strip of
   pixels whose upper left corner is at position 
   (column,0), and whose width is width.
*/
void Block::build(PNG & im, int column, int width){
  // stub
}

/* Draws the current block at position
   (column,0) in im.
*/
void Block::render(PNG & im, int column) const {
	// stub
}

/* This function changes the saturation of 
   every pixel in the block to 0, which
   removes the color, leaving grey.
*/
void Block::greyscale(){
	// stub
}

int Block::width() const {
	return 0; // stub FIXME
}

int Block::height() const {
  return 0; // stub FIXME
}