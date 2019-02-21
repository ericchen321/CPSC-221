#include "rainbowColorPicker.h"
#include <math.h>

using std::pair;
using std::map;

rainbowColorPicker::rainbowColorPicker(long double freq_) : iter(0), freq(freq_)
{
}

HSLAPixel rainbowColorPicker::operator()(int x, int y)
{
    PNGmap::iterator stored = prev.find(pair<int, int>(x, y));
    if (stored == prev.end()) {
        HSLAPixel next = nextColor();
        prev[pair<int, int>(x, y)] = next;
        return next;
    } else
        return stored->second;
}

// http://www.krazydad.com/makecolors.php
HSLAPixel rainbowColorPicker::nextColor()
{
    HSLAPixel ret;
    if (iter * freq > 1) iter = 0;
    ret.h = (360 * iter * freq);
    ret.s = 1.0;
    ret.l = 0.5;
    iter++;
    return ret;
}
