/**
 * @file filler.h
 * Defintion of a filler namespace.
 *
 */
#ifndef _FILLER_H_
#define _FILLER_H_

#include "cs221util/PNG.h"
#include "stack.h"
#include "queue.h"
#include "animation.h"


#include "rainbowColorPicker.h" // given as an example
#include "borderColorPicker.h"
#include "stripeColorPicker.h"
using namespace cs221util;

/**
 * filler namespace: specifies a set of functions for performing flood
 * fills on images. 
 *
 */
namespace filler
{
        /**
         * Performs a flood fill on the given image using a stripe,
         * employing a depth-first-search approach.
         *
         * @param img The image to be filled.
         * @param x The starting x coordinate for the fill.
         * @param y The starting y coordinate for the fill.
         * @param fillColor The color the stripes should appear.
         * @param stripeSpacing The width of the stripe spacing.
         * @param tolerance How different colors are allowed to be to still be
         * included in the fill.
         * @param frameFreq How frequently to add a frame to the animation, in
         *  pixels. For instance, if frameFreq == 1, a frame is added when every
         *  pixel is filled. If frameFreq == 10, a frame is added after every 10
         *  pixels is filled.
         * @return An animation that shows the fill progressing over the image.
         */
        animation fillStripeDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                           int stripeSpacing, double tolerance, int frameFreq);

        /**
         * Performs a flood fill on the given image but only colors the 
         * border of the fill region.  Employs a depth-first-search approach.
         *
         * @param img The image to be filled.
         * @param x The starting x coordinate for the fill.
         * @param y The starting y coordinate for the fill.
         * @param fillColor The color the border should appear.
         * @param tolerance How far away colors are allowed to be to still be
         * included in the fill.
         * @param frameFreq How frequently to add a frame to the animation, in
         *  pixels. For instance, if frameFreq == 1, a frame is added when every
         *  pixel is filled. If frameFreq == 10, a frame is added after every 10
         *  pixels is filled.
         * @return An animation that shows the fill progressing over the image.
         */

        animation fillBorderDFS(PNG& img, int x, int y, HSLAPixel borderColor,
                double tolerance, int frameFreq);

        /**
         * Performs a flood fill on the given image using a stripe,
         * employing a breadth-first-search approach.
         *
         * @param img The image to be filled.
         * @param x The starting x coordinate for the fill.
         * @param y The starting y coordinate for the fill.
         * @param fillColor The color the stripes should appear.
         * @param stripeSpacing The width of the stripe spacing.
         * @param tolerance How different colors are allowed to be to still be
         * included in the fill.
         * @param frameFreq How frequently to add a frame to the animation, in
         *  pixels. For instance, if frameFreq == 1, a frame is added when every
         *  pixel is filled. If frameFreq == 10, a frame is added after every 10
         *  pixels is filled.
         * @return An animation that shows the fill progressing over the image.
         */
        animation fillStripeBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                int stripeSpacing, double tolerance, int frameFreq);

        /**
         * Performs a flood fill on the given image but only colors the 
         * border of the fill region.  Employs a breadth-first-search approach.
         *
         * @param img The image to be filled.
         * @param x The starting x coordinate for the fill.
         * @param y The starting y coordinate for the fill.
         * @param fillColor The color the border should appear.
         * @param tolerance How far away colors are allowed to be to still be
         * included in the fill.
         * @param frameFreq How frequently to add a frame to the animation, in
         *  pixels. For instance, if frameFreq == 1, a frame is added when every
         *  pixel is filled. If frameFreq == 10, a frame is added after every 10
         *  pixels is filled.
         * @return An animation that shows the fill progressing over the image.
         */

        animation fillBorderBFS(PNG& img, int x, int y, HSLAPixel borderColor,
                double tolerance, int frameFreq);

        /* The following two functions are given to you as examples of 
         * working fill functions.
        */
        animation fillRainDFS(PNG& img, int x, int y, 
                long double freq, double tolerance, int frameFreq);
        animation fillRainBFS(PNG& img, int x, int y, 
                long double freq, double tolerance, int frameFreq);


    /**
     * Filling function: a general helper that should be invoked by
     * ALL of the public fill functions parameterized by the appropriate 
     * color picker for that type of fill.
     *
     * @param img Image to do the filling on.
     * @param x X coordinate to start the fill from.
     * @param y Y coordinate to start the fill from.
     * @param fillColor The colorPicker function object to be used for the fill.
     * @param tolerance How different colors are allowed to be to still be
     *  included in the fill.
     * @param frameFreq How frequently to add a frame to the animation, in
     *  pixels. For instance, if frameFreq == 1, a frame is added when every
     *  pixel is filled. If frameFreq == 10, a frame is added after every 10
     *  pixels is filled.
     * @return An animation that shows the fill progressing over the image.
     */
    template <template <class T> class OrderingStructure>
    animation fill(PNG& img, int x, int y, colorPicker& fillColor,
                   double tolerance, int frameFreq);
}
#include "filler.cpp"
#endif
