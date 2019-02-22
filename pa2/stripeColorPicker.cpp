#include "stripeColorPicker.h"

stripeColorPicker::stripeColorPicker(HSLAPixel fillColor, int stripeSpacing)
{
/* your code here! */
  color = fillColor;
  spacing = stripeSpacing;
}

HSLAPixel stripeColorPicker::operator()(int x, int y)
{
/* your code here! */
  if(x % spacing == 0){
    return color;
  }
  else{
    return HSLAPixel();
  }
}
