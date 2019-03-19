
#ifndef _STATS_H
#define _STATS_H

#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
#include <utility>
#include <cmath>
#include <vector>
using namespace std;
using namespace cs221util;

#define PI 3.14159265

class stats {

//private:
public:
	vector< vector< double >> sumHueX;
	vector< vector< double >> sumHueY;
	vector< vector< double >> sumSat;
	vector< vector< double >> sumLum;

    /* hist[i][j][k]: hist[i][j] contains a histogram of the hue values 
    *   0 to 360 into bins of width 10, over the pixels in the rectangle
    *   defined by (0,0) through (i,j). For example, hist[i][j][k] contains
    *   the number of pixels whose hue value h, is: k*10 <= h < (k+1)*10. 
    */
    vector<vector<vector<int>>> hist;

public:

	// initialize all private vectors so that, for each color channel, 
	// (x,y) is the cumulative sum of the the color values from (0,0)
	// to (x,y), and the hist structure is as defined above.
    // Note that the hue (h) value of each pixel is represented by
    // its cartesian coordinates: X = s*cos(h) and Y = s*sin(h). 
    // This is done to simplify distance computation. We calculate
    // the cumulative sums for X and Y separately, and then combine
    // them when we are doing color difference computation.
	stats(PNG & im); 

	// given a rectangle, return the average color value over the rect.
	/* Each color component of the pixel is the average value of that 
	* component over the rectangle.
	* @param ul is (x,y) of the upper left corner of the rectangle 
	* @param lr is (x,y) of the lower right corner of the rectangle */
    // The average hue value can be computed from the average X and
    // Y values using the arctan function. You should research the 
    // details of this. Finally, please set the average alpha channel to 
    // 1.0.
	HSLAPixel getAvg(pair<int,int> ul, pair<int,int> lr);

	// given a rectangle, return the number of pixels in the rectangle
	/* @param ul is (x,y) of the upper left corner of the rectangle 
	* @param lr is (x,y) of the lower right corner of the rectangle */
	long rectArea(pair<int,int> ul, pair<int,int> lr);

    // given any rectangle, build a histogram of color frequencies
    // over the rectangle using the hist private member variable
    // described above.
    vector<int> buildHist(pair<int,int> ul, pair<int,int> lr);

    // given any rectangle, return the total entropy over that rect.
	/* @param ul is (x,y) of the upper left corner of the rectangle 
	* @param lr is (x,y) of the lower right corner of the rectangle */
    /* entropy is computed from the (private member) distn table, as 
     * follows: E = -Sum(p_i log(p_i)), where p_i is the fraction of
     * pixels in bin i, and the sum is taken over all the bins. 
     * bins holding no pixels should not be included in the sum. */
    double entropy(pair<int,int> ul, pair<int,int> lr);

    // given a distribution over colors, and the area of the region,
    // return the total entropy.
    /* entropy is computed from the distn parameter, as 
     * follows: E = -Sum(p_i log(p_i)), where p_i is the fraction of
     * pixels in bin i, and the sum is taken over all the bins. 
     * bins holding no pixels should not be included in the sum. */
    double entropy(vector<int> & d ,int area);
};

#endif
