// kAVLTree.cpp

#include "kAVLTree.h"

#include <iostream>
#include <string>
#include <queue>
#include <cmath>    // abs

// Constructs a k-AVLTree with parameter k
kAVLTree::kAVLTree(int k) : k(k), root(nullptr)
{}

// Inserts node with value 'whole.frac' if it was not previously in the tree
// Prints "'whole.frac' inserted" if it was inserted
void kAVLTree::printInsert(int whole, int frac)
{
    const NodeVal val(whole, frac);
    std::queue<Node*> recent;
    this->root = printInsertRecurs(val, this->root, recent);
}

// Prints "'whole.frac' found" if it is in the tree
void kAVLTree::printSearch(int whole, int frac) const
{
    NodeVal nv(whole, frac);    // node value to search for

    Node* n = this->root;
    while (n)
    {
        if (nv < n->value)
        {   // Search left subtree
            n = n->left;
        }

        else if (nv > n->value)
        {   // Search right subtree
            n = n->right;
        }

        else // nv == n->value
        {   // Found node, so print and return
            std::cout << nv.toString() << " found" << std::endl;
            return;
        }
    }
    
    // Now, n == nullptr, so the node is not in the tree
    std::cout << nv.toString() << " not found" << std::endl;
}

// Prints "closest to 'whole.frac' is 'closest_whole.closest_frac'"
void kAVLTree::printApproxSearch(int whole, int frac) const
{
    if (this->root == nullptr)
    {   // Tree is empty, so print nothing
        return;
    }

    NodeVal nv(whole, frac);    // Node value to approximate-search for

    std::queue<NodeVal> recent;  // Queue to track up to 2 most-recently visited nodes

    Node* n = this->root;
    while (n)
    {
        if (recent.size() == 2)
        {
            recent.pop();
        }
        recent.push(n->value);

        if (nv < n->value)
        {   // Search left subtree
            n = n->left;
        }

        else if (nv > n->value)
        {   // Search right subtree
            n = n->right;
        }

        else // nv == n->value
        {   // Found node, so print and return
            std::cout << nv.toString() << " found" << std::endl;
            return;
        }
    }

    // Once we hit a nullptr, we know the node is not in the tree
    // But, we are where the node being searched for would be if it existed
    // And, the queue holds the only two relevant nodes needed to find the closest one
    // So, we will compare the queue's two nodes' values and print which one is closest
    //  If both are equally close, then we will print the least of the two

    NodeVal closest(-1, -1);    // Stores closest NodeVal, for readability

    if (recent.size() == 1)
    {
        closest = recent.front();
        recent.pop();
    }

    else    // recent.size() == 2
    {
        NodeVal first = recent.front();
        NodeVal second = recent.back();

        if (first - nv < second - nv)
        {
            closest = first;
        }

        else if (first - nv > second - nv)
        {
            closest = second;
        }

        else    // first - nv == second - nv
        {
            closest = first < second ? first : second;
        }
    }

    std::cout << "closest to " << nv.toString() << " is " << closest.toString() << std::endl;
}

// Prints the node values in-order
void kAVLTree::printInOrder() const
{
    if (root == nullptr)
    {   // Tree is empty, so print nothing
        return;
    }

    std::string keysInOrder = printInOrderRecurs(this->root);
    keysInOrder.resize(keysInOrder.size() - 1);     // Leave out the last space
    std::cout << keysInOrder << std::endl;
}

// Prints the node values pre-order
void kAVLTree::printPreOrder() const
{
	if (root == nullptr)
	{	// Tree is empty, so print nothing
		return;
	}

	std::string keysPreOrder = printPreOrderRecurs(this->root);
    keysPreOrder.resize(keysPreOrder.size() - 1);   // Leave out the last space
	std::cout << keysPreOrder << std::endl;
}

// Recursive helper for printInsert
// Returns a pointer to the new root of the subtree after inserting and self-balancing
// Self-balancing is done during pre-order, where the AVL height property is broken
//  Then, a single- or double- rotation is performed to rebalance
// The queue, recent, stores at most the 2 most-recently visited descendents during the recursive backtrack
kAVLTree::Node* kAVLTree::printInsertRecurs(NodeVal const& nv, Node* n, std::queue<Node*>& recent)
{
    /* First, insert the node and print so (if it does not already exist) */

    if (n == nullptr)
    {   // Reached end, so insert, print, push to queue, and return
        std::cout << nv.toString() << " inserted" << std::endl;
        Node* newNode = createNode(nv.whole, nv.fract);
        recent.push(newNode);
        return newNode;
    }

    if (nv == n->value)
    {   // Node already exists, so do nothing and return
        return n;
    }

    if (nv < n->value)
    {   // Insert into left subtree
        n->left = printInsertRecurs(nv, n->left, recent);
    }

    else // nv > n->value
    {   // Insert into right subtree
        n->right = printInsertRecurs(nv, n->right, recent);
    }

    // TO-DO: Implement Second part (below)
    /*  Second:
     *     Check if the height property has been broken
     *          If it has been broken, then:
     *              1. Determine which case (1-4)
     *              2. Perform single- or double- rotation to rebalance (depending on step 1)
     *              3. Update the heights of X, Y, Z
     *              4. Clear the queue
     *              5. Return the corresponding new root (determined in step 2)
     *          If it hasn't been broken, then:
     *              1. Add this Node to the size-2 queue
     *              2. Update the height of this node
     *              3. Return this node
     */
    
    /* Check for height imbalance */
    
    if (isImbalanced(n) )
    {   // Height imbalance
        // Determine case and run its specific rotation function
        Node* y = recent.back();    // Y is the child of Z that leads to the insertion location
        Node* x = recent.front();   // X is the child of Y that leads to the insertion location
        recent.pop(); // Empty the queue because rotations will make queue information undefined
        recent.pop();

        Node* newRoot = nullptr;    // Store new root, for readability

        if (y == n->left)
        {
            if (x == y->left)
            {   // Case 1
                newRoot = rotateCW(n); // Rotate Y, Z clockwise
                // std::cout << "case 1 with (Z = " << n->value.toString() << ", Y = " << y->value.toString() << ", X = " << x->value.toString() << ")" << std::endl;
            }

            else    // x == y->right
            {   // Case 3
                n->left = rotateCounterCW(y);   // Rotate X, Y counter-clockwise
                                                // Now, X is Z's left child
                newRoot = rotateCW(n); // Rotate X, Z clockwise
                // std::cout << "case 3 with (Z = " << n->value.toString() << ", Y = " << y->value.toString() << ", X = " << x->value.toString() << ")" << std::endl;
            }
        }

        else    // y == n->right
        {
            if (x == y->left)
            {   // Case 4
                n->right = rotateCW(y); // Rotate X, Y clockwise
                                        // Now, X is Z's right child
                newRoot = rotateCounterCW(n);  // Rotate X, Z counter-clockwise
                // std::cout << "case 4 with (Z = " << n->value.toString() << ", Y = " << y->value.toString() << ", X = " << x->value.toString() << ")" << std::endl;
            }

            else    // x == y->right
            {   // Case 2
                newRoot = rotateCounterCW(n);    // Rotate Y, Z counter-clockwise
                // std::cout << "case 2 with (Z = " << n->value.toString() << ", Y = " << y->value.toString() << ", X = " << x->value.toString() << ")" << std::endl;
            }
        }

        return newRoot; // Return the new root
    }

    else    // No height imbalance
    {
        // Update the height of this node
        updateHeight(n);
        
        // Update the queue, recent
        if (recent.size() == 2)
        {
            recent.pop();
        }
        recent.push(n);

        return n;
    }

    return nullptr; // Should not be reached?
}
    }

    // TO-DO: Implement Second part (below)
    /*  Second:
     *      Update the height of this node
     *      Check if the height property has been broken
     *          If it has been broken, then perform single- or double- rotation to rebalance
    */

// Returns new root after rotating the left child and the current node clockwise
kAVLTree::Node* kAVLTree::rotateCW(Node* n)
{
    Node* leftChild = n->left;  // Store Y
    n->left = leftChild->right; // Set Z's left to Y's right (where Z is current node and Y is Z's left child)
    leftChild->right = n;       // Set Y's right to Z

    // Update heights bottom-up
    updateHeight(n);
    updateHeight(leftChild);

    return leftChild;           // Return Y as new root
}

// Returns new root after rotating the right child and the current node counter-clockwise
kAVLTree::Node* kAVLTree::rotateCounterCW(Node* n)
{
    Node* rightChild = n->right; // Store Y
    n->right = rightChild->left; // Set Z's right to Y's left (where Z is current node and Y is Z's right child)
    rightChild->left = n;        // Set Y's left to Z

    // Update heights bottom-up
    updateHeight(n);
    updateHeight(rightChild);

    return rightChild;           // Return Y as new root
}

// Updates the height of the given node
// Note: Non-existent children are treated with height -1
void kAVLTree::updateHeight(Node* n)
{
    // Determine the heights of the left and right subtrees
    int leftHeight = n->left ? n->left->height : -1;
    int rightHeight = n->right ? n->right->height : -1;

    // Set this node's height
    n->height = std::max(leftHeight, rightHeight) + 1;
    //std::cout << "New height of " << n->value.toString() << " is " << n->height << std::endl;
}

// Returns true iff a height imbalance is seen at the given node
bool kAVLTree::isImbalanced(Node* n) const
{
    // Determine the heights of the left and right subtrees
    int leftHeight = n->left ? n->left->height : -1;
    int rightHeight = n->right ? n->right->height : -1;
    
    // Return true iff the height difference is greater than k
    return abs(leftHeight - rightHeight) > k;
}

// Recursive helper for printInOrder
// Returns a string of the nodes in the tree with root n in-order, space-separated
std::string kAVLTree::printInOrderRecurs(Node* n) const
{
    if (n == nullptr)
    {
        return "";
    }

    return printInOrderRecurs(n->left) + n->value.toString() + " " + printInOrderRecurs(n->right);
}

// Recursive helper for printPreOrder
// Returns a string of the nodes in the tree with root n pre-order, space-separated
std::string kAVLTree::printPreOrderRecurs(Node* n) const
{
	if (n == nullptr)
	{
		return "";
	}

	return n->value.toString() + " " + printPreOrderRecurs(n->left) + printPreOrderRecurs(n->right);
}

// Returns a newly-created node with input parameter values
kAVLTree::Node* kAVLTree::createNode(int whole, int frac) const
{
    return new Node(whole, frac);
}

/** START: Node member functions **/

// Parameterized Constructor
kAVLTree::Node::Node(int whole, int fract) : height(0), value(whole, fract), left(nullptr), right(nullptr)
{}

/** END: Node member functions **/

/** START: NodeVal member functions **/

// Parameterized constructor
kAVLTree::NodeVal::NodeVal(int whole, int fract) : whole(whole), fract(fract)
{}

// Overloaded assignment operator
kAVLTree::NodeVal& kAVLTree::NodeVal::operator=(NodeVal const& other)
{
    this->whole = other.whole;
    this->fract = other.fract;
	return *this;
}

// Overloaded equality operator
bool kAVLTree::NodeVal::operator==(NodeVal const& other) const
{
    return this->whole == other.whole && this->fract == other.fract;
}

// Overloaded less than operator
bool kAVLTree::NodeVal::operator<(NodeVal const& other) const
{
    return this->whole < other.whole || (this->whole == other.whole && this->fract < other.fract);
}

// Overloaded greater than operator
bool kAVLTree::NodeVal::operator>(NodeVal const& other) const
{
    return this->whole > other.whole || (this->whole == other.whole && this->fract > other.fract);
}

// Overloaded subtraction operator
kAVLTree::NodeVal kAVLTree::NodeVal::operator-(NodeVal const& other) const
{
    return NodeVal(this->whole - other.whole, this->fract - other.fract);
}

// Returns a string of 'whole.fract'
std::string kAVLTree::NodeVal::toString() const
{
    return std::to_string(this->whole) + "." + std::to_string(this->fract);
}
