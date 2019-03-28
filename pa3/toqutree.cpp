
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
			*(im->getPixel(x, y)) = 
			*(imIn.getPixel((x_offset+x), (y_offset+y)));
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
	int lr_y = ul_y + POW2(k-1) - 1;

	// both bounded
	if(ul_x >= 0 && lr_x < POW2(k)
			&& ul_y >= 0 && lr_y < POW2(k)){
		vector<int> hist_all = s.buildHist({ul_x, ul_y}, {lr_x, lr_y});
		double area = s.rectArea({ul_x, ul_y}, {lr_x, lr_y});
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
			hist_left = s.buildHist({0, ul_y}, {MOD(lr_x, POW2(k)), lr_y});
			area_left = s.rectArea({0, ul_y}, {MOD(lr_x, POW2(k)), lr_y});
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
	assert(ctr_x>=0 && ctr_x<POW2(k) && ctr_y>=0 && ctr_y<POW2(k));

	// build histograms for each of the four sub-squares
	return (totalEntropy(s, k, ctr_x, ctr_y) // SE
					+ totalEntropy(s, k, ctr_x-POW2(k-1), ctr_y) // SW
					+ totalEntropy(s, k, ctr_x, ctr_y-POW2(k-1)) // NE
					+ totalEntropy(s, k, ctr_x-POW2(k-1), ctr_y-POW2(k-1))) // NW
					/ 4.0;
}

void toqutree::buildImage(PNG* im, int k, int ul_x, int ul_y, PNG * &img){
	int side_length = POW2(k-1);
	img = new PNG(side_length, side_length);

	for(int y=0; y<side_length; y++){
		for(int x=0; x<side_length; x++){
			*(img->getPixel(x, y)) =  *(im->getPixel(MOD(ul_x+x, POW2(k)), MOD(ul_y+y, POW2(k))));	
		}
	}
}

void toqutree::buildImages(PNG* im, int k, int ctr_x, int ctr_y, PNG * &imgNW, PNG * &imgNE, PNG * &imgSE, PNG * &imgSW){
	// build individual images
	buildImage(im, k, ctr_x, ctr_y, imgSE); // SE
	buildImage(im, k, ctr_x-POW2(k-1), ctr_y, imgSW); // SW
	buildImage(im, k, ctr_x, ctr_y-POW2(k-1), imgNE); // NE
	buildImage(im, k, ctr_x-POW2(k-1), ctr_y-POW2(k-1), imgNW); //NW
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
	// initialize the croot node
	stats s(*(im));
	int dim = k;
	//cout << "building tree of k = " << k << endl;
	HSLAPixel avg = s.getAvg({0,0}, {POW2(k)-1, POW2(k)-1});
	/*
	if(k==0){
		cout << "tree buildin " << "hue: " << avg.h << " sat: " << avg.s << " lum: " << avg.l << endl;
	}
	*/
	Node* croot = new Node({0, 0}, dim, avg);

	// recursive case: given node is not a pixel
	if(k > 0){
		// find the split point
		if(k == 1){
			croot->center = {1, 1};
		}
		else{
			double avg_entropy;
			double avg_entropy_min = DBL_MAX;
			for(int x=((POW2(k)-POW2(k-1))/2); x<((POW2(k)+POW2(k-1))/2); x++){
				for(int y=((POW2(k)-POW2(k-1))/2); y<((POW2(k)+POW2(k-1))/2); y++){
					avg_entropy = averageEntropy(s, k, x, y);
					if(avg_entropy < avg_entropy_min){
						croot->center = {x, y};
						avg_entropy_min = avg_entropy;
					}
				}
			}
		}

		// build images for the four children
		PNG* imgNW; PNG* imgNE; PNG* imgSE; PNG* imgSW;
		buildImages(im, k, croot->center.first, croot->center.second, imgNW, imgNE, imgSE, imgSW);

		// build the sub-trees
		croot->NW = buildTree(imgNW, k-1);
		croot->NE = buildTree(imgNE, k-1);
		croot->SE = buildTree(imgSE, k-1);
		croot->SW = buildTree(imgSW, k-1);
	}

	// clear the croot's image
	delete(im);

	return croot;
}

void toqutree::render(Node * croot, vector<pair<int, int>>uls, PNG * img){
	if(croot == NULL){
		return;
	}

	// leaf node: drawing pixels
	if(croot->NE==NULL && croot->NW==NULL && croot->SE==NULL && croot->SW==NULL){
		int side_length = POW2(croot->dimension);
		int map_count = uls.size();
		for(int y=0; y<side_length; y++){
			for(int x=0; x<side_length; x++){
				int x_global = x;
				int y_global = y;
				//cout << "x = " << x << ", y = " << y << endl;
				for(int i=0; i<map_count; i++){
					x_global += uls[map_count-i-1].first;
					x_global = MOD(x_global, POW2(croot->dimension+i+1));
					y_global += uls[map_count-i-1].second;
					y_global = MOD(y_global, POW2(croot->dimension+i+1));
					//cout << "i= " << i << " array idx: " << (map_count-i-1) << " ul x: " << uls[map_count-i-1].first << " ul y:" << uls[map_count-i-1].second << " x global: " << x_global << " y global:" << y_global << endl;
				}
				assert(x_global>=0 && x_global<(int)img->width() && y_global>=0 && y_global<(int)img->height());

				//cout << "renderin " << x_global << "," << y_global << "," << "hue: " << croot->avg.h << " sat: " << croot->avg.s << " lum: " << croot->avg.l << endl;
				*(img->getPixel(x_global, y_global)) = croot->avg;
			}
		}
	}

	// non-leaf node: render sub-squares
	else {
		int ctr_x = croot->center.first;
		int ctr_y = croot->center.second;
		int k = croot->dimension;
		vector<pair<int, int>> ne = uls; ne.push_back({ctr_x, ctr_y-POW2(k-1)});
		render(croot->NE, ne, img);
		vector<pair<int, int>> nw = uls; nw.push_back({ctr_x-POW2(k-1), ctr_y-POW2(k-1)});
		render(croot->NW, nw, img);
		vector<pair<int, int>> se = uls; se.push_back({ctr_x, ctr_y});
		render(croot->SE, se, img);
		vector<pair<int ,int>> sw = uls; sw.push_back({ctr_x-POW2(k-1), ctr_y});
		render(croot->SW, sw, img);
	}
}

PNG toqutree::render(){

// My algorithm for this problem included a helper function
// that was analogous to Find in a BST, but it navigated the 
// quadtree, instead.

/* your code here */
	PNG canvas(POW2(root->dimension), POW2(root->dimension));
	vector<pair<int, int>> init_ul; init_ul.push_back({0, 0});
	render(root, init_ul, &canvas);
	return canvas;
}

bool toqutree::allInTolerence(Node * croot, HSLAPixel pixel, double tol){
	assert(croot != NULL);

	// base case: node is a pixel
	if(croot->dimension == 0){
		return (pixel.dist(croot->avg) <= tol);
	}
	
	// recursive case: node is a square
	return (allInTolerence(croot->NE, pixel, tol)
					&& allInTolerence(croot->NW, pixel, tol)
					&& allInTolerence(croot->SE, pixel, tol)
					&& allInTolerence(croot->SW, pixel, tol));
}

void toqutree::makeLeaf(Node * croot){
	clear(croot->NE); 
	clear(croot->NW); 
	clear(croot->SE);
	clear(croot->SW);
}

void toqutree::prune(Node * & croot, double tol){
	if(allInTolerence(croot, croot->avg, tol)){
		makeLeaf(croot);
	}
	else{
		prune(croot->NE, tol);
		prune(croot->NW, tol);
		prune(croot->SE, tol);
		prune(croot->SW, tol);
	}
}

/* oops, i left the implementation of this one in the file! */
void toqutree::prune(double tol){
	prune(root,tol);
}

/* called by destructor and assignment operator*/
void toqutree::clear(Node * & curr){
/* your code here */
	// FIXME: why the heck am I not using private helper???
	if(curr == NULL)
		return;
	
	clear(curr->NE);
	clear(curr->NW);
	clear(curr->SE);
	clear(curr->SW);
	delete(curr);
	curr = NULL;
}

/* done */
/* called by assignment operator and copy constructor */
toqutree::Node * toqutree::copy(const Node * other) {

/* your code here */
	// FIXME: well not using helper...
	if(other == NULL){
		return NULL;
	}

	Node* new_node = new Node(other->center, other->dimension, other->avg);
	new_node->NE = copy(other->NE);
	new_node->NW = copy(other->NW);
	new_node->SE = copy(other->SE);
	new_node->SW = copy(other->SW);
	return new_node;
}


