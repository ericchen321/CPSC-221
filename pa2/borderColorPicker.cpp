#include "borderColorPicker.h"

borderColorPicker::borderColorPicker(HSLAPixel fillColor, PNG & img, double tolerance,HSLAPixel center)
{
/* Your code here! */
  color = fillColor;
  im = img;
  tol = tolerance;
  ctr = center;
}

HSLAPixel borderColorPicker::operator()(int x, int y)
{

/* Your code here! */
  int distSqr;
  for(int i=-3; i<=3; i++){
    for(int j=-3; j<=3; j++){
      distSqr = i^2+j^2;
      if(distSqr <= 9 
          && isWithinImage(x+i, y+j, im.width(), im.height()) 
          && isWithinFillRegion(x+i, y+j)){}
      else{
        return color;
      }
    }
  }
  return *(im.getPixel((unsigned int)x, (unsigned int)y));
}

bool borderColorPicker::isWithinImage(int x, int y, unsigned int imgWidth, unsigned int imgHeight){
  int w = (int) imgWidth;
  int h = (int) imgHeight;
  return (w>0 && h>0 && x>=0 && x<w && y>=0 && y<h);
}

bool borderColorPicker::isWithinFillRegion(int x, int y){
  HSLAPixel *p = im.getPixel((unsigned int)x, (unsigned int)y);
  double dist = p->dist(ctr);
  return (dist>=(-1*tol) && dist<=tol);
}