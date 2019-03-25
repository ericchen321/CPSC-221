
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
	unsigned int x_offset = (imIn.width() - POW2(k)) / 2;
	unsigned int y_offset = (imIn.height() - POW2(k)) / 2;
	PNG* im = new PNG((POW2(k)), (POW2(k)));

	for(unsigned int y=0; y<POW2(k); y++){
		for(unsigned int x=0; x<POW2(k); x++){
			*(im->getPixel(x, y)) = *(imIn.getPixel(x_offset+x, y_offset+y));
		}
	}

	root = buildTree(im, k);
}

int toqutree::size() {
/* TODO your code here */
	return 0;
}

double toqutree::averageEntropy(stats &s, int k, int ctr_x, int ctr_y){
	return 0.0;
}

void toqutree::buildImages(PNG* im, int ctr_x, int ctr_y, PNG *imgNW, PNG *imgNE, PNG *imgSE, PNG *imgSW){
	
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
			for(unsigned int y=((POW2(k)-POW2(k-1))/2); y<((POW2(k)+POW2(k-1))/2); y++){
				for(unsigned int x=((POW2(k)-POW2(k-1))/2); x<((POW2(k)+POW2(k-1))/2); x++){
					avg_entropy = averageEntropy(s, k, x, y);
					if(avg_entropy <= avg_entropy_min){
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


