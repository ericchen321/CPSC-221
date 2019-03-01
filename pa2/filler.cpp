/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. 
 *
 */
//#include "filler.h"

animation filler::fillStripeDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int stripeSpacing, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
    stripeColorPicker s(fillColor, stripeSpacing);
    return fill<Stack>(img, x, y, s, tolerance, frameFreq);
}

animation filler::fillBorderDFS(PNG& img, int x, int y,
                                    HSLAPixel borderColor, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
    borderColorPicker b(borderColor, img, tolerance, *(img.getPixel(x, y)));
    return fill<Stack>(img, x, y, b, tolerance, frameFreq);
}

/* Given implementation of a DFS rainbow fill. */
animation filler::fillRainDFS(PNG& img, int x, int y,
                                    long double freq, double tolerance, int frameFreq)
{
    rainbowColorPicker a(freq);
    return fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillStripeBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int stripeSpacing, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
    stripeColorPicker s(fillColor, stripeSpacing);
    return fill<Queue>(img, x, y, s, tolerance, frameFreq);
}

animation filler::fillBorderBFS(PNG& img, int x, int y,
                                    HSLAPixel borderColor, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     */
    borderColorPicker b(borderColor, img, tolerance, *(img.getPixel(x, y)));
    return fill<Queue>(img, x, y, b, tolerance, frameFreq);
}

/* Given implementation of a BFS rainbow fill. */
animation filler::fillRainBFS(PNG& img, int x, int y,
                                    long double freq, double tolerance, int frameFreq)
{
    rainbowColorPicker a(freq);
    return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillCustomDFS(PNG& img, int x, int y, 
                        HSLAPixel color0, HSLAPixel color1, double tolerance, int frameFreq)
{
    customColorPicker c(color0, color1);
    return fill<Stack>(img, x, y, c, tolerance, frameFreq);
}

animation filler::fillCustomBFS(PNG& img, int x, int y, 
                        HSLAPixel color0, HSLAPixel color1, double tolerance, int frameFreq)
{
    customColorPicker c(color0, color1);
    return fill<Queue>(img, x, y, c, tolerance, frameFreq);
}

template <template <class T> class OrderingStructure>
animation filler::fill(PNG& img, int x, int y, colorPicker& fillColor,
                       double tolerance, int frameFreq)
{
    /**
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a Queue, for a depth-first-search, that
     * structure is a Stack. To begin the algorithm, you simply place the
     * given point in the ordering structure, marking it processed
     * (the way you mark it is a design decision you'll make yourself).
     * We have a choice to either change the color, if appropriate, when we
     * add the point to the OS, or when we take it off. In our test cases,
     * we have assumed that you will change the color when a point is added
     * to the structure. 
     *
     * Until the structure is empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure, and then...
     *
     *        1.    add its unprocessed neighbors whose color values are 
     *              within (or equal to) tolerance distance from the center, 
     *              to the ordering structure.
     *        2.    use the colorPicker to set the new color of the neighbrs.
     *        3.    mark the neighbors as processed.
     *        4.    as you process a neighbor, if it is an appropriate frame, 
     *              send the current PNG to the animation (as described below).
     *
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        For this assignment, each pixel p has 8 neighbors, consisting of 
     *        the 8 pixels who share an edge or corner with p. (We leave it to
     *        you to describe those 8 pixel locations, relative to the location
     *        of p.)
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! 
     *
     *        The order you should put
     *        neighboring pixels **ONTO** the ordering structure (queue or stack) 
     *        is as follows: **UPRIGHT(+x,-y), UP(-y), UPLEFT(-x,-y), LEFT(-x), 
     *        DOWNLEFT(-x,+y), DOWN(+y), DOWNRIGHT(+x,+y), RIGHT(+x)**
     *
     *        If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     *        IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction.  
     *
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     * 4.     Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and 
     *        it will be the one we test against.
     */
    animation anime;
    OrderingStructure<PixelRecord> os;
    int fillCount = 0;
    vector<vector<PixelRecord>> imgMatrix;
    imgMatrix.resize(img.height());
    for(unsigned int i=0; i<img.height(); i++){
        imgMatrix[i].resize(img.width());
        for(unsigned int j=0; j<img.width(); j++){
            PixelRecord p;
            p.x = j;
            p.y = i;
            p.beforeProcessing = *(img.getPixel((unsigned int)j, (unsigned int)i));
            p.processed = false;
            imgMatrix[i][j] = p;
        }
    }

    if(fillPixel(x, y, x, y, tolerance, imgMatrix, os, img, fillColor)){
        fillCount += 1;
        processFrame(anime, img, fillCount, frameFreq);
    }
    
    while(!os.isEmpty()){
        PixelRecord ctr = os.remove();

        if(fillPixel(ctr.x+1, ctr.y-1, x, y, tolerance, imgMatrix, os, img, fillColor)){
            fillCount += 1;
            processFrame(anime, img, fillCount, frameFreq);
        }

        if(fillPixel(ctr.x, ctr.y-1, x, y, tolerance, imgMatrix, os, img, fillColor)){
            fillCount += 1;
            processFrame(anime, img, fillCount, frameFreq);
        }

        if(fillPixel(ctr.x-1, ctr.y-1, x, y, tolerance, imgMatrix, os, img, fillColor)){
            fillCount += 1;
            processFrame(anime, img, fillCount, frameFreq);
        }

        if(fillPixel(ctr.x-1, ctr.y, x, y, tolerance, imgMatrix, os, img, fillColor)){
            fillCount += 1;
            processFrame(anime, img, fillCount, frameFreq);
        }

        if(fillPixel(ctr.x-1, ctr.y+1, x, y, tolerance, imgMatrix, os, img, fillColor)){
            fillCount += 1;
            processFrame(anime, img, fillCount, frameFreq);
        }

        if(fillPixel(ctr.x, ctr.y+1, x, y, tolerance, imgMatrix, os, img, fillColor)){
            fillCount += 1;
            processFrame(anime, img, fillCount, frameFreq);
        }

        if(fillPixel(ctr.x+1, ctr.y+1, x, y, tolerance, imgMatrix, os, img, fillColor)){
            fillCount += 1;
            processFrame(anime, img, fillCount, frameFreq);
        }

        if(fillPixel(ctr.x+1, ctr.y, x, y, tolerance, imgMatrix, os, img, fillColor)){
            fillCount += 1;
            processFrame(anime, img, fillCount, frameFreq);
        }
    }

    if(fillCount != 0)
        anime.addFrame(img);
    
    return anime;
}

bool filler::fillPixel(int x, int y, 
                       int ctr_x, int ctr_y, double tol, 
                       vector<vector<PixelRecord>>& imgMatrix,
                       OrderingStructure<PixelRecord>& os, 
                       PNG& img, 
                       colorPicker& fillColor){
    //cout << "processing pixel " << x << " " << y << endl;
    if(isWithinImage(x, y, img)){
        PixelRecord& given = imgMatrix[y][x];
        if(given.processed == false
            && isWithinFillRegion(x, y, ctr_x, ctr_y, imgMatrix, tol))
        {
            *(img.getPixel(x, y)) = fillColor(x, y);
            given.processed = true;
            os.add(given);
            //cout << "processed pixel " << x << " " << y << endl;
            return true;
        }
        else{
            return false;
        }
    }
    return false;
}

bool filler::isWithinImage(int x, int y, PNG& img){
    int w = (int) img.width();
    int h = (int) img.height();
    return (w>0 && h>0 && x>=0 && x<w && y>=0 && y<h);
}

bool filler::isWithinFillRegion(int x, int y, int ctr_x, int ctr_y, 
                                vector<vector<PixelRecord>>& imgMatrix, 
                                double tol){
    HSLAPixel pixel = imgMatrix[y][x].beforeProcessing;
    HSLAPixel center = imgMatrix[ctr_y][ctr_x].beforeProcessing;
    double dist = pixel.dist(center);
    //cout << "dist: " << dist <<endl;
    return dist<=tol;
}

void filler::processFrame(animation& anime, PNG& img, int& fillCount, int frameFreq){
    if(fillCount == frameFreq){
        anime.addFrame(img);
        fillCount = 0;
    }
}