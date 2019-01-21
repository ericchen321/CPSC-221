/* mocked block implementations */

#include <iostream>
#include "../cs221util/PNG.h"
#include "block.h"

using namespace std;

Block::Block(){
  return;
}

Block::Block(int n){
  data_ = n;
}

void Block::build(PNG & im, int column, int width) {
  return;
}

void Block::render(PNG & im, int column) const {
  return;
}

void Block::greyscale() {
  return;
}

int Block::width() const {
  return 1;
}

int Block::height() const {
  return 1;
}

int Block::data() const{
  return data_;
}