
// File:        main.cpp
// Author:      cheeren
// Date:        2019-03-04
// Description: Partial test of PA3 functionality


#include "cs221util/HSLAPixel.h"
#include "cs221util/PNG.h"
#include "toqutree.h"

using namespace cs221util;
using namespace std;

int main()
{
	PNG origIm0;
	origIm0.readFromFile("images/smB.png");
	toqutree t0(origIm0, 3);
	PNG ppic0 = t0.render();
	ppic0.writeToFile("images/output-smB.png");

	/*
	// read in an image
	PNG origIm1;
	origIm1.readFromFile("images/canadaPlace.png");

	// use it to build a toqutree
	toqutree t1(origIm1,8);

    // make some copies for pruning tests
	toqutree tCopy1(t1);
	toqutree tCopy2(t1);
	toqutree tCopy3(t1);
	toqutree tCopy4(t1);

	// prune the toqutree
	//where all subtree pixels are within Y of mean

	tCopy1.prune(.2); 
	tCopy2.prune(.1); 
	tCopy3.prune(.05); 
	tCopy4.prune(.025); 

	// render the toqutree
    PNG ppic1 = t1.render();
    PNG ppiccopy1 = tCopy1.render();
    PNG ppiccopy2 = tCopy2.render();
    PNG ppiccopy3 = tCopy3.render();
    PNG ppiccopy4 = tCopy4.render();

    // write the pngs to files.
	ppic1.writeToFile("images/output-CP.png");
	ppiccopy1.writeToFile("images/output-CP.2.png");
	ppiccopy2.writeToFile("images/output-CP.1.png");
	ppiccopy3.writeToFile("images/output-CP.05.png");
	ppiccopy4.writeToFile("images/output-CP.025.png");
	*/
	PNG origIm2;
	origIm2.readFromFile("images/ada.png");
	toqutree t2(origIm2, 9);
	t2.prune(0.05);
	PNG ppic2 = t2.render();
	ppic2.writeToFile("images/output-adaPrune-.05.png");

	PNG origIm3;
	origIm3.readFromFile("images/stanleySquare.png");
	toqutree t3(origIm3, 9);
	PNG ppic3 = t3.render();
	ppic3.writeToFile("images/output-stanleySquare.png");

  return 0;
}

