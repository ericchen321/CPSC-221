#include "HSLAPixel.h"

namespace cs221util {
    HSLAPixel::HSLAPixel(){
        h = 0;
        s = 0;
        l = 1.0;
        a = 1.0;
    }

    HSLAPixel::HSLAPixel(double h1, double s1, double l1){
        h = h1;
        s = s1;
        l = l1;
    }

    HSLAPixel::HSLAPixel(double h1, double s1, double l1, double a1){
        HSLAPixel::HSLAPixel(h1, s1, l1);
        a = a1;
    }
}