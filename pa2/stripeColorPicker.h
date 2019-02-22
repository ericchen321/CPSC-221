/**
 * @file stripeColorPicker.h
 * Definition of a stripe color picker.
 *
 */
#ifndef STRIPECOLORPICKER_H
#define STRIPECOLORPICKER_H

#include "colorPicker.h"

/**
 * stripeColorPicker: a functor that determines the color that should be used
 * given an x and a y coordinate using a stripe pattern.
 *
 */
class stripeColorPicker : public colorPicker
{
  public:
    /**
     * Constructs a new stripeColorPicker.
     *
     * @param fillColor Color for the stripes.
     * @param stripeSpacing space between the stripes
     */
    stripeColorPicker(HSLAPixel fillColor, int stripeSpacing);

    /**
     * Picks the color for pixel (x, y). If the x coordinate is a
     * multiple of the spacing, it will be filled with the fillColor.
     * otherwise, it will be filled with white.
     *
     * @param x The x coordinate to pick a color for.
     * @param y The y coordinat to pick a color for.
     * @return The color chosen for (x, y).
     */
    virtual HSLAPixel operator()(int x, int y);

  private:
    HSLAPixel color; /**< Color used for the stripe. */
    int spacing;     /**< Space between stripes. */
};

#endif
