
#include "stats.h"

stats::stats(PNG & im){

/* your code here */
    int width = im.width();
    int height = im.height();
    sumHueX.resize(height);
    sumHueY.resize(height);
    sumSat.resize(height);
    sumLum.resize(height);
    hist.resize(height);

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            if(i==0 && j==0){
                sumHueX[i].push_back(cos(toRad(im.getPixel(j, i)->h)));
                sumHueY[i].push_back(sin(toRad(im.getPixel(j, i)->h)));
                sumSat[i].push_back(im.getPixel(j, i)->s);
                sumLum[i].push_back(im.getPixel(j, i)->l);
            }
            else if(j==0){
                sumHueX[i].push_back(cos(toRad(im.getPixel(j, i)->h)) + sumHueX[i-1][width-1]);
                sumHueY[i].push_back(sin(toRad(im.getPixel(j, i)->h)) + sumHueY[i-1][width-1]);
                sumSat[i].push_back(im.getPixel(j, i)->s + sumSat[i-1][width-1]);
                sumLum[i].push_back(im.getPixel(j, i)->l + sumLum[i-1][width-1]);
            }
            else{
                sumHueX[i].push_back(cos(toRad(im.getPixel(j, i)->h)) + sumHueX[i][j-1]);
                sumHueY[i].push_back(sin(toRad(im.getPixel(j, i)->h)) + sumHueY[i][j-1]);
                sumSat[i].push_back(im.getPixel(j, i)->s + sumSat[i][j-1]);
                sumLum[i].push_back(im.getPixel(j, i)->l +sumLum[i][j-1]);
            }
        }
    }

    for(int i=0; i<height; i++){
        hist[i].resize(width);
        for(int j=0; j<width; j++){
            hist[i][j].resize(36);
            for(int k=0; k<36; k++){
                hist[i][j][k] = 0;
                if(i>0){
                    hist[i][j][k] += hist[i-1][j][k];
                }
                if(j>0){
                    hist[i][j][k] += hist[i][j-1][k];
                }
                if(i>0 && j>0){
                    hist[i][j][k] -= hist[i-1][j-1][k];
                }
                
                if(k*10 <= (int)im.getPixel(j, i)->h 
                    && (int)im.getPixel(j, i)->h < (k+1)*10){
                    hist[i][j][k] += 1;
                }  
            }
        }
    }
}

long stats::rectArea(pair<int,int> ul, pair<int,int> lr){

/* your code here */
    // TODO: now assuming not having to deal with shifting
    assert(ul.first>=0 && ul.second>=0
            && lr.first < (int)hist[0].size() && lr.second < (int)hist.size()
            && lr.first >= ul.first && lr.second >= ul.second);

    int width = lr.first - ul.first + 1;
    int height = lr.second - ul.second + 1;
    return (long)(width * height);
}

HSLAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){

/* your code here */
    // TODO: now assuming not having to deal with shifting
    assert(ul.first>=0 && ul.second>=0
            && lr.first < (int)hist[0].size() && lr.second < (int)hist.size()
            && lr.first >= ul.first && lr.second >= ul.second);

    double area = (double)rectArea(ul, lr);
    double sumHX, sumHY, sumS, sumL;
    
    sumHX = sumHueX[lr.second][lr.first];
    sumHY = sumHueY[lr.second][lr.first];
    sumS = sumSat[lr.second][lr.first];
    sumL = sumLum[lr.second][lr.first];

    if(ul.second > 0){
        sumHX -= sumHueX[ul.second-1][lr.first];
        sumHY -= sumHueY[ul.second-1][lr.first];
        sumS -= sumSat[ul.second-1][lr.first];
        sumL -= sumLum[ul.second-1][lr.first];
    }
    if(ul.first > 0){
        sumHX -= sumHueX[lr.second][ul.first-1];
        sumHY -= sumHueY[lr.second][ul.first-1];
        sumS -= sumSat[lr.second][ul.first-1];
        sumL -= sumLum[lr.second][ul.first-1];
    }
    if(ul.second>0 && ul.first>0){
        sumHX += sumHueX[ul.second-1][ul.first-1];
        sumHY += sumHueY[ul.second-1][ul.first-1];
        sumS += sumSat[ul.second-1][ul.first-1];
        sumL += sumLum[ul.second-1][ul.first-1];
    }

    double avg_hue = toDeg(atan2((sumHY/area), (sumHX/area)));

    HSLAPixel pixel = HSLAPixel(avg_hue, sumS/area, sumL/area, 1.0);

    return pixel;
}

vector<int> stats::buildHist(pair<int,int> ul, pair<int,int> lr){

/* your code here */
    // TODO: now assuming not having to deal with shifting
    assert(ul.first>=0 && ul.second>=0
            && lr.first < (int)hist[0].size() && lr.second < (int)hist.size()
            && lr.first >= ul.first && lr.second >= ul.second);

    vector<int> hist_of_rec;
    hist_of_rec.resize(36);

    for(int i=0; i<36; i++){
        hist_of_rec[i] = hist[lr.second][lr.first][i];

        if(ul.second > 0){
            hist_of_rec[i] -= hist[ul.second-1][lr.first][i];
        }
        if(ul.first > 0){
            hist_of_rec[i] -= hist[lr.second][ul.first-1][i];
        }
        if(ul.second>0 && ul.first>0){
            hist_of_rec[i] += hist[ul.second-1][ul.first-1][i];
        }
    }

    return hist_of_rec;
}

// takes a distribution and returns entropy
// partially implemented so as to avoid rounding issues.
double stats::entropy(vector<int> & distn,int area){

    double entropy = 0.;

/* your code here */

    for (int i = 0; i < 36; i++) {
        if (distn[i] > 0 ) 
            entropy += ((double) distn[i]/(double) area) 
                                    * log2((double) distn[i]/(double) area);
    }

    return  -1 * entropy;

}

double stats::entropy(pair<int,int> ul, pair<int,int> lr){

/* your code here */
    // TODO: now assuming not having to deal with shifting
    assert(ul.first>=0 && ul.second>=0
            && lr.first < (int)hist[0].size() && lr.second < (int)hist.size()
            && lr.first >= ul.first && lr.second >= ul.second);

    vector<int> hist = buildHist(ul, lr);
    long area = rectArea(ul, lr);
    return entropy(hist, (int)area);
}
