#ifndef CS221UTIL_HSLAPIXEL_H
#define CS221UTIL_HSLAPIXEL_H

namespace cs221util {
    class HSLAPixel
    {
    public:
        double h, s, l, a;
        HSLAPixel();
        HSLAPixel(double h1, double s1, double l1);
        HSLAPixel(double h1, double s1, double l1, double a1);
    };
}

#endif