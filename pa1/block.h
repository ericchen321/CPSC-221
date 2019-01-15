
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
   void build(PNG & im, int column, int width);
   void render(PNG & im, int column) const ;
   void greyscale();
   int width() const ;
   int height() const ;

private:

   vector< vector < HSLAPixel > > data;

};
#endif
