#include "block.h"
#include "cs221util/PNG.h"

/* requires: 0 <= column < im.width and
             width >= 0 and
             (column + width) <= im.width
             FIXME: get rid of the requires later
   effects: From im, grabs the vertical strip of
            pixels whose upper left corner is at position 
            (column,0), and whose width is width.
*/
void Block::build(PNG & im, int column, int width){
  unsigned int col_bound = column + width;
  unsigned int row_bound = im.height();
  data.resize(im.height());
  for (unsigned int row=0; row<row_bound; row++){
    data[row].resize(width);
    for (unsigned int col=column; col<col_bound; col++){
      data[row][col-(unsigned)column] = *(im.getPixel(col, row));
    }
  }
  //cout << "block width " << data[0].size() << endl;
  //cout << "block height " << data.size() << endl;
}

/* requires: column + block width <= im.width()
   effects: Draws the current block at position
            (column,0) in im.
*/
void Block::render(PNG & im, int column) const {
	if (!(column>=0 && column<im.width()))
    return;
  unsigned int col_bound = (column + width() > im.width())? im.width() : (column + width());
  for (unsigned int col = column; col<col_bound; col++){
    for (unsigned int row = 0; row<im.height(); row++){
      *(im.getPixel(col, row)) = data[row][col-(unsigned)column];
    }
  }
}

/* This function changes the saturation of 
   every pixel in the block to 0, which
   removes the color, leaving grey.
*/
void Block::greyscale(){
	for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      data[y][x].s = 0;
    }
  }
}

/*  Returns the width of the current block
*/
int Block::width() const {
	if(data.size() == 0){
    return 0;
  }
  
  return data[0].size();
}

/* Returns the height of the current block.
*/
int Block::height() const {
  
  return data.size();
}