
/**
 *
 * toqutree (pa3)
 * significant modification of a quadtree .
 * toqutree.cpp
 * This file will be used for grading.
 *
 */

#include "toqutree.h"

toqutree::Node::Node(pair<int,int> ctr, int dim, HSLAPixel a)
	:center(ctr),dimension(dim),avg(a),NW(NULL),NE(NULL),SE(NULL),SW(NULL)
	{}

toqutree::~toqutree(){
	clear(root);
}

toqutree::toqutree(const toqutree & other) {
	root = copy(other.root);
}


toqutree & toqutree::operator=(const toqutree & rhs){
	if (this != &rhs) {
		clear(root);
		root = copy(rhs.root);
	}
	return *this;
}

toqutree::toqutree(PNG & imIn, int k){ 

/* This constructor grabs the 2^k x 2^k sub-image centered */
/* in imIn and uses it to build a quadtree. It may assume  */
/* that imIn is large enough to contain an image of that size. */

/* your code here */
	int x_offset = (imIn.width() - POW2(k)) / 2;
	int y_offset = (imIn.height() - POW2(k)) / 2;
	PNG* im = new PNG((POW2(k)), (POW2(k)));

	for(int y=0; y<POW2(k); y++){
		for(int x=0; x<POW2(k); x++){
			*(im->getPixel((unsigned int)x, (unsigned int)y)) = 
			*(imIn.getPixel((unsigned int)(x_offset+x), (unsigned int)(y_offset+y)));
		}
	}

	root = buildTree(im, k);
}

int toqutree::size() {
/* TODO your code here */
	return 0;
}

double toqutree::totalEntropy(stats &s, int k, int ul_x, int ul_y){
	assert(k>=2);

	int lr_x = ul_x + POW2(k-1) - 1;
	int lr_y = lr_y + POW2(k-1) - 1;
	double area, entropy;

	// both bounded
	if(ul_x >= 0 && lr_x < POW2(k)
			&& ul_y >= 0 && lr_y < POW2(k)){
		vector<int> hist_all = s.buildHist({ul_x, ul_y}, {lr_x, lr_y});
		area = s.rectArea({ul_x, ul_y}, {lr_x, lr_y});
		return s.entropy(hist_all, area);
	}

	// y bounded
	else if(ul_y >= 0	&& lr_y < POW2(k)){
		vector<int> hist_left, hist_right, hist_all;
		hist_all.resize(36);
		double area_left, area_right;
		if(ul_x<0){
			hist_left = s.buildHist({0, ul_y}, {lr_x, lr_y});
			area_left = s.rectArea({0, ul_y}, {lr_x, lr_y});
			hist_right = s.buildHist({MOD(ul_x, POW2(k)), ul_y}, {POW2(k)-1, lr_y});
			area_right = s.rectArea({MOD(ul_x, POW2(k)), ul_y}, {POW2(k)-1, lr_y});
		}
		else{
			hist_left = s.buildHist({0, ul_x}, {MOD(lr_x, POW2(k)), lr_y});
			area_left = s.rectArea({0, ul_x}, {MOD(lr_x, POW2(k)), lr_y});
			hist_right = s.buildHist({ul_x, ul_y}, {POW2(k)-1, lr_y});
			area_right = s.rectArea({ul_x, ul_y}, {POW2(k)-1, lr_y});
		}
		for(int i=0; i<36;i++){
				hist_all[i] = hist_left[i] + hist_right[i];
		}
		return s.entropy(hist_all, area_left+area_right);
	}

	// x bounded
	else if(ul_x >= 0 && lr_x < POW2(k)){
		vector<int> hist_upper, hist_lower, hist_all;
		hist_all.resize(36);
		double area_upper, area_lower;
		if(ul_y<0){
			hist_upper = s.buildHist({ul_x, 0}, {lr_x, lr_y});
			area_upper = s.rectArea({ul_x, 0}, {lr_x, lr_y});
			hist_lower = s.buildHist({ul_x, MOD(ul_y, POW2(k))}, {lr_x, POW2(k)-1});
			area_lower = s.rectArea({ul_x, MOD(ul_y, POW2(k))}, {lr_x, POW2(k)-1});
		}
		else{
			hist_upper = s.buildHist({ul_x, 0}, {lr_x, MOD(lr_y, POW2(k))});
			area_upper = s.rectArea({ul_x, 0}, {lr_x, MOD(lr_y, POW2(k))});
			hist_lower = s.buildHist({ul_x, ul_y}, {lr_x, POW2(k)-1});
			area_lower = s.rectArea({ul_x, ul_y}, {lr_x, POW2(k)-1});
		}
		for(int i=0; i<36;i++){
			hist_all[i] = hist_upper[i] + hist_lower[i];
		}
		return s.entropy(hist_all, area_upper+area_lower);
	}

	// neither bounded
	else{
		vector<int> hist_UL, hist_UR, hist_LL, hist_LR, hist_all;
		hist_all.resize(36);
		double area_UL, area_UR, area_LL, area_LR;
		pair<int, int> UL_ul = {MOD(ul_x, POW2(k)), MOD(ul_y, POW2(k))};
		pair<int, int> LR_lr = {MOD(lr_x, POW2(k)), MOD(lr_y, POW2(k))};
		pair<int, int> LL_ul = {MOD(ul_x, POW2(k)), 0};
		pair<int, int> UR_ul = {0, MOD(ul_y, POW2(k))};
		hist_LR = s.buildHist({0, 0}, LR_lr);
		area_LR = s.rectArea({0, 0}, LR_lr);
		hist_LL = s.buildHist(LL_ul, {POW2(k)-1, LR_lr.second});
		area_LL = s.rectArea(LL_ul, {POW2(k)-1, LR_lr.second});
		hist_UR = s.buildHist(UR_ul, {LR_lr.first, POW2(k)-1});
		area_UR = s.rectArea(UR_ul, {LR_lr.first, POW2(k)-1});
		hist_UL = s.buildHist(UL_ul, {POW2(k)-1, POW2(k)-1});
		area_UL = s.rectArea(UL_ul, {POW2(k)-1, POW2(k)-1});
		for(int i=0; i<36; i++){
			hist_all[i] = hist_UL[i] + hist_UR[i] + hist_LL[i] + hist_LR[i];
		}
		return s.entropy(hist_all, area_LL+area_LR+area_UL+area_UR);
	}
}

double toqutree::averageEntropy(stats &s, int k, int ctr_x, int ctr_y){
	// build histograms for each of the four sub-squares
	return (totalEntropy(s, k, ctr_x, ctr_y) // SE
					+ totalEntropy(s, k, ctr_x-POW2(k), ctr_y) // SW
					+ totalEntropy(s, k, ctr_x, ctr_y-POW2(k)) // NE
					+ totalEntropy(s, k, ctr_x-POW2(k), ctr_y-POW2(k))) // NW
					/ 4.0;
}

void toqutree::buildImages(PNG* im, int ctr_x, int ctr_y, PNG *imgNW, PNG *imgNE, PNG *imgSE, PNG *imgSW){
	// TODO
}

toqutree::Node* toqutree::buildTree(PNG * im, int k) {

/* your code here */

// Note that you will want to practice careful memory use
// In this function. We pass the dynamically allocated image
// via pointer so that it may be released after it is used .
// similarly, at each level of the tree you will want to 
// declare a dynamically allocated stats object, and free it
// once you've used it to choose a split point, and calculate
// an average.
	// initialize the root node
	stats s(*(im));
	int dim = k;
	HSLAPixel avg = s.getAvg({0,0}, {POW2(k)-1, POW2(k)-1});
	Node* root = new Node({0, 0}, dim, avg);

	// recursive case: given node is not a pixel
	if(k > 0){
		// find the split point
		if(k == 1){
			root->center = {1, 1};
		}
		else{
			double avg_entropy;
			double avg_entropy_min = DBL_MAX;
			for(int x=((POW2(k)-POW2(k-1))/2); x<((POW2(k)+POW2(k-1))/2); x++){
				for(int y=((POW2(k)-POW2(k-1))/2); y<((POW2(k)+POW2(k-1))/2); y++){
					avg_entropy = averageEntropy(s, k, x, y);
					if(avg_entropy < avg_entropy_min){
						root->center = {x, y};
					}
				}
			}
		}

		// build images for the four children
		PNG* imgNW; PNG* imgNE; PNG* imgSE; PNG* imgSW;
		buildImages(im, root->center.first, root->center.second, imgNW, imgNE, imgSE, imgSW);

		// build the sub-trees
		root->NW = buildTree(imgNW, k/2);
		root->NE = buildTree(imgNE, k/2);
		root->SE = buildTree(imgSE, k/2);
		root->SW = buildTree(imgSW, k/2);
	}

	// clear the root's image
	delete(im);

	return root;
}

PNG toqutree::render(){

// My algorithm for this problem included a helper function
// that was analogous to Find in a BST, but it navigated the 
// quadtree, instead.

/* your code here */

}

/* oops, i left the implementation of this one in the file! */
void toqutree::prune(double tol){

	//prune(root,tol);

}

/* called by destructor and assignment operator*/
void toqutree::clear(Node * & curr){
/* your code here */
}

/* done */
/* called by assignment operator and copy constructor */
toqutree::Node * toqutree::copy(const Node * other) {

/* your code here */
}


