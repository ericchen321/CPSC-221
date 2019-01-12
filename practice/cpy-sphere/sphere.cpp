#include "sphere.h"

// copy constructor
sphere::sphere(const sphere &orig){
    theRadius = orig.theRadius;
    numAtts = orig.numAtts;
    atts = new string[numAtts];
    for (int i=0; i<numAtts; i++){
        atts[i] = orig.atts[i]; // Q: why ccstor need for heap?
    }
}