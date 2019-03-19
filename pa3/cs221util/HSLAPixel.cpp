/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

#define PI 3.14159265

namespace cs221util {
  HSLAPixel::HSLAPixel() {
    h = 0;
    s = 0;
    l = 1.0;
    a = 1.0;
  }

  HSLAPixel::HSLAPixel(double hue, double saturation, double luminance) {
    h = hue;
    s = saturation;
    l = luminance;
    a = 1.0;
  }

  HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha) {
    h = hue;
    s = saturation;
    l = luminance;
    a = alpha;
  }

  HSLAPixel & HSLAPixel::operator=(HSLAPixel const & other) {
    this->h = other.h;
    this->s = other.s;
    this->l = other.l;
    this->a = other.a;
    return *this;
  }

  bool HSLAPixel::operator== (HSLAPixel const & other) const {

    return dist(other) < 0.007;
    /*if (fabs(a - other.a) > 0.01) { return false; }
    if ( a == 0 ) { return true; }

    if (fabs(l - other.l) > 0.01) { return false; }
    if (l == 0 || l == 1) { return true; }

    if (fabs(s - other.s) > 0.01) { return false; }
    if (s == 0) { return true; }

    if (fabs(h - other.h) < 0.5 || fabs(h - other.h) > 359.5 ) { return true; }
    else { return false; }*/
}

  bool HSLAPixel::operator!= (HSLAPixel const & other) const {
    return !(*this == other);
  }

  bool HSLAPixel::operator<  (HSLAPixel const & other) const {
      if (*this == other) { return false; }

      if (l < other.l)
          return true;
      else if (l > other.l)
          return false;
      // == lumininance

      if (s < other.s)
          return true;
      else if (s > other.s)
          return false;
      // == saturation

      if (h < other.h)
          return true;
      else if (h > other.h)
          return false;
      // == hue

      if (a < other.a)
          return true;
      else if (a > other.a)
          return false;
      // == alpha

      // same pixel
      return false;
  }

  std::ostream & operator<<(std::ostream & out, HSLAPixel const & pixel) {
    out << "(" << pixel.h << ", " << pixel.s << ", " << pixel.l << (pixel.a != 1 ? ", " + std::to_string(pixel.a) : "") << ")";

    return out;
  }

double HSLAPixel::dist(HSLAPixel p) const
{
return (sin(h*PI/180.)*s*l - sin(p.h*PI/180.)*p.s*p.l )
    *(sin(h*PI/180.)*s*l - sin(p.h*PI/180.)*p.s*p.l )
 + ( cos(h*PI/180.)*s*l - cos(p.h*PI/180.)*p.s*p.l )
    * ( cos(h*PI/180.)*s*l - cos(p.h*PI/180.)*p.s*p.l )
 + ( l - p.l ) * (l - p.l);
}


}
