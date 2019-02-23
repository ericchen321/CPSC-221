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

    struct PixelRecord{
        int x;
        int y;
        HSLAPixel beforeProcessing;
        bool processed;
    };

    /* effects: If pixel of given (x, y) is unprocessed, and is within 
     *          boundary of given image, and is within fill region, 
     *          then adds its PixelRecord to given ordering structure, 
     *          marks it as processed, and fills it with given color picker. 
     *          Returns true if pixel of given (x, y) is actually filled.
     *          If given pixel fails any condition above then return false.
     */
    bool fillPixel(int x, int y, 
                   int ctr_x, int ctr_y, double tol, 
                   vector<vector<PixelRecord>>& imgMatrix,
                   OrderingStructure<PixelRecord>& os, 
                   PNG& img, 
                   colorPicker& fillColor);

    /*
     * effects: returns true if given pixel is within the boundary 
     *          of the given image;
     *          false otherwise.
     */
    bool isWithinImage(int x, int y, PNG& img);

    /*
     * requires: given pixel is within boudary of given image
     * effects: returns true if given pixel is within fill region, 
     *          as indicated by the center point and tolerence;
     *          returns false otherwise.
     */
    bool isWithinFillRegion(int x, int y, int ctr_x, int ctr_y, 
                            vector<vector<PixelRecord>>& imgMatrix, double tol);

    /* 
     * Adds a new frame to given animation if fillCount overflows.
     * Resets fillCount to 0 after an overflow.
     * @param: anime animation in which a new frame may be added
     * @param: img image after last fill
     * @param: fillCount number of pixels actually filled since last frame
     * @param: frameFreq frame frequency, requires this > 0
     */
    void processFrame(animation& anime, PNG& img, int& fillCount, int frameFreq);
}
#include "filler.cpp"
#endif
