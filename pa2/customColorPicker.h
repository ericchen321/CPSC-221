/**
 * @file customColorPicker.h
 * Definition of a custom color picker.
 *
 */
#ifndef CUSTOMCOLORPICKER_H
#define CUSTOMCOLORPICKER_H

#include "colorPicker.h"

class customColorPicker : public colorPicker
{
  public:
    customColorPicker(HSLAPixel fillColor0, HSLAPixel fillColor1);
    virtual HSLAPixel operator()(int x, int y);

  private:
    HSLAPixel color0;
    HSLAPixel color1;
};

#endif