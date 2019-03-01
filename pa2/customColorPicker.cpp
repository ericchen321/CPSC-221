#include "customColorPicker.h"

customColorPicker::customColorPicker(HSLAPixel fillColor0, HSLAPixel fillColor1)
{
/* your code here! */
  color0 = fillColor0;
  color1 = fillColor1;
}

HSLAPixel customColorPicker::operator()(int x, int y)
{
/* your code here! */
  if((x + y) % 2 == 0){
    return color0;
  }
  else{
    return color1;
  }
}