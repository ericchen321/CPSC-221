
/**
 *
 * toqutree (pa3)
 * slight modification of a quad tree wherein the
 * splitting location can vary across the region.
 */

#ifndef _TOQUTREE_H_
#define _TOQUTREE_H_

#include <utility>
#include <cmath>
#include <float.h>
#include <assert.h>
#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
#include "stats.h"

#define POW2(k) (int)pow(2, k)
#define MOD(a, b) (int)((a % b + b) % b)

using namespace std;
using namespace cs221util;

/**
 * toqutree: This is a structure used in decomposing an image
 * into rectangles and squares of similarly colored pixels.
 *
 * You should not remove anything from this class definition, but
 * you will find it helpful to add your own private helper functions to it.
 *
 * This file will be used for grading.
 */

class toqutree {
private:

   /**
    * The Node class is private to the tree class via the principle of
    * encapsulation---the end user does not need to know our node-based
    * implementation details.
    * 
    * Assumes the current node is a 2^dim x 2^dim square whose upper left
    * corner is 0,0, and whose bottom right corner (inclusive) is 
    * 2^dim-1,2^dim-1.
    */
   class Node {
   public:

      Node(pair<int,int> ctr, int dim, HSLAPixel a);

        pair<int,int> center; // optimal splitting position 
        int dimension; // node represents a square, 2^dim x 2^dim in size
        HSLAPixel avg; // average color over square

      Node * NW; // left top child 
      Node * NE; // right top child 
      Node * SE; // right bottom child
      Node * SW; // left bottom child 
      
   };
	
   
public:

   /* =============== start of given functions ====================*/

   /**
    * toqutree destructor.
    * Destroys all of the memory associated with the
    * current toqutree. This function should ensure that
    * memory does not leak on destruction of a toqutree.
    * 
    * @see toqutree_given.cpp
    */
   ~toqutree();

   /**
    * Copy constructor for a toqutree. GIVEN
    * Since toqutrees allocate dynamic memory (i.e., they use "new", we
    * must define the Big Three). This depends on your implementation
    * of the copy funtion.
    * @see toqutree_given.cpp
    *
    * @param other The toqutree  we are copying.
    */
   toqutree(const toqutree & other);

   /**
    * Overloaded assignment operator for toqutrees. 
    * Part of the Big Three that we must define because the class
    * allocates dynamic memory. This depends on your implementation
    * of the copy and clear funtions.
    *
    * @param rhs The right hand side of the assignment statement.
    */
   toqutree & operator=(const toqutree & rhs);


   /* =============== end of given functions ====================*/

   /* =============== public PA3 FUNCTIONS =========================*/

   /**
    * Constructor that builds a toqutree out of the given PNG.
    * Every leaf in the tree corresponds to a pixel in the PNG.
    * Every non-leaf node corresponds to a square of pixels 
    * which may not be contiguous in the original PNG, due to .
    * the splittingg procedure we've chosen. In addition, the Node
    * stores a pixel representing the average color over the 
    * portion of the image it represents.
    *
    * Every node's children correspond to a partition
    * of the node's square into four smaller squares where a square
    * is defined under the assumption that the image's horizontal
    * and vertical borders "wrap" so that pixels at the top are 
    * considered to be adjacent to pixels at the bottom, and similarly
    * for the right and left edges of the image. The node's
    * square is partitioned by choosing a splitting point that
    * results in the four smaller squares whose Information Gain
    * is as large as possible. See the website for description.
    *
    * The children of a node are named NW, NE, SE, and SW corresponding
    * to the compass directions, and assuming N is up.
    * (see illustrations within the spec.)
    *
   * This function will call helper function buildTree.
    */

   toqutree(PNG & imIn,int k);

   /**
    * Render returns a PNG image consisting of the pixels
    * stored in the tree. may be used on pruned trees. Draws
    * every pixel onto a PNG canvas using the 
    * average color stored in the node.
    */
   PNG render();

   /*
    *  Prune function trims subtrees as high as possible in the tree.
    *  A subtree is pruned (cleared) if ALL of the subtree's leaves are within 
    *  tol of the average color stored in the root of the subtree. 
    *  Pruning criteria should be evaluated on the original tree, not 
    *  on any pruned subtree. (we only expect that trees would be pruned once.)
    *  
   * You may want a recursive helper function for this one.
    */
   void prune(double tol);

    /* returns the number of nodes in the current toqutree. primarily used
     * for debugging and testing.
     */
    int size();

   /* =============== end of public PA3 FUNCTIONS =========================*/

private:
   /*
    * Private member variables.
    *
    * You must use these as specified in the spec and may not rename them.
    * You may add more if you need them.
    */

   Node* root; // ptr to the root of the toqutree


   /* =================== private PA3 functions ============== */
   /* for you to implement */

   /**
    * Destroys all dynamically allocated memory associated with the
    * current toqutree class. Complete for PA3.
   * You may want a recursive helper function for this one.
    */
   void clear(Node * &croot);

   /**
   * Copies the parameter other toqutree into the current toqutree.
   * Does not free any memory. Called by copy constructor and op=.
   * You may want a recursive helper function for this one.
   * @param other The toqutree to be copied.
   */
   Node * copy(const Node * croot);

   /**
   * Private helper function for the constructor. Recursively builds
   * the tree according to the specification of the constructor.
   * @param: PNG * im, a pointer to a 2^k by 2^k image.
   * @param: int k, the dimension of the image (note that this is redundant--could just be grabbed from the image itself)
   */
   Node * buildTree(PNG * im, int k);

   /**
    * Returns the average entropy of the four squares after splitting the
    * parent square about (ctr_x, ctr_y). 
    * @param s stats of the parent square.
    * @param k dimension of the parent square. Requires k>=2.
    * @param ctr_x ctr_y split point. Requires (ctr_x, ctr_y) within (0,0)
    *        to (2^k-1, 2^k-1).
    */
   double averageEntropy(stats &s, int k, int ctr_x, int ctr_y);

   /**
    * Returns the total entropy of the square whose upper-left corner
    * is at (ul_x, ul_y) of the parent square.
    * @param s stats of the parent square image.
    * @param k dimension of the parent square. Requires k>=2.
    * @param ul_x ul_y upper-left corner coordinate of the square. Each
    *        coordinate may be <0 or >=2^k due to wrapping.
    */
   double totalEntropy(stats &s, int k, int ul_x, int ul_y);

   /**
    * Build images of the four squares after splitting the parent square,
    * represented by im.
    * @param im ptr to parent square's image.
    * @param k parent square's dimension.
    * @param ctr_x ctr_y split point. Requires being a well-defined pt in
    *        im.
    * @param imgNW, imgNE, imgSE, imgSW ptr to images of four child squares.
    *        The function should initialize the image pointers it takes.
    */
   void buildImages(PNG* im, int k, int ctr_x, int ctr_y, PNG * &imgNW, PNG * &imgNE, PNG * &imgSE, PNG * &imgSW);

   /**
    * Build image of a sub-square from image of the parent square.
    * @param im ptr to parent square's image.
    * @param k parent square's dimension.
    * @param ul_x ul_y ul_x ul_y upper-left corner coordinate of the square. Each
    *        coordinate may be <0 or >=2^k due to wrapping.
    * @param img pointer to the sub-square's image. Should be initialized by this
    *        function.
    */
   void buildImage(PNG* im, int k, int ul_x, int ul_y, PNG* &img);

   /* Helper for the public prune method. Prune the given tree with given 
    * tolerence.
    */
   void prune(Node * & croot, double tol);

   /* Returns true if all pixels in the tree under croot are within
    * tolerence of the given pixel. False if not.
    */
   bool allInTolerence(Node * croot, HSLAPixel pixel, double tol);

   /* Makes the given croot node a leaf node. 
    */ 
   void makeLeaf(Node * croot);

   /* Private helper function for render(). Renders all pixels in the given
    * tree on the given canvas.
    * @param croot root of the given tree. May or may not be a leaf.
    * @param uls list of (ul_x, ul_y) of squares along the split path, from
    *        the 0th split at (0, 0) to the most recent split which yields
    *        croot. The list should have at least one pair. The points may
    *        be beyond the border of given canvas due to wrapping.
    * @param img ptr to PNG where the tree is rendered. Required being
    *        initialized and larger or equal to the size defined by croot's
    *        dimension.
    */
   void render(Node * croot, vector<pair<int, int>>uls, PNG * img);
   /* =================== end of private PA3 functions ============== */
};

#endif
