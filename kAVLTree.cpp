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
    this->root = printInsertRecurs(val, this->root);
}

// Deletes the node wih the value 'whole.frac' if it exists
// Prints "'whole.frac' deleted" if it was deleted
void kAVLTree::printDelete(int whole, int frac)
{
    const NodeVal val(whole, frac);
    bool deleted = false;
    this->root = printDeleteRecurs(val, this->root, deleted);
    if (deleted)
    {
        std::cout << val.toString() << " deleted" << std::endl;
}
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
kAVLTree::Node* kAVLTree::printInsertRecurs(NodeVal const& nv, Node* n)
{
    /* First, insert the node and print so (if it does not already exist) */

    if (n == nullptr)
    {   // Reached end, so insert, print, and return
        std::cout << nv.toString() << " inserted" << std::endl;
        return createNode(nv.whole, nv.fract);
    }

    if (nv == n->value)
    {   // Node already exists, so do nothing and return
        return n;
    }

    if (nv < n->value)
    {   // Insert into left subtree
        n->left = printInsertRecurs(nv, n->left);
    }

    else // nv > n->value
    {   // Insert into right subtree
        n->right = printInsertRecurs(nv, n->right);
    }
    
    /* Check for height imbalance after deleting */
    
    if (isImbalanced(n) )
    {   // Height imbalance, so rebalance it
        return rebalance(n);
    }

    else    // No height imbalance
    {
        // Update the height of this node
        updateHeight(n);
        
kAVLTree::Node* kAVLTree::printDeleteRecurs(NodeVal const& nv, Node* n, bool& deleted)
    }
}

// Similar to printInsertRecurs, except deletes a given node if it exists (and then rebalances if needed)
kAVLTree::Node* kAVLTree::printDeleteRecurs(NodeVal const& nv, Node* n)
{
    /* First, delete the node and print so (if it does already exist) */

    if (n == nullptr)
    {   // Reached end, so do nothing and return
        return nullptr;
        // Set deleted tag to true
        deleted = true;

    }

    if (nv == n->value)
    {   // Found the node to delete

        // If the node is a leaf, then delete it and return
        if (n->left == nullptr && n->right == nullptr)
        {
            delete n;
            return nullptr;
        }

            n->left = printDeleteRecurs(pred->value, n->left, deleted);
        if (n->left)
        {
            Node* pred = getPredecessor(n->left);
            n->value = pred->value;
            n->left = printDeleteRecurs(pred->value, n->left);
        }
    
        // Else, the node has a right subtree, so delete it and return its right child
        else
        {
            Node* rightChild = n->right;
            delete n;
            return rightChild;
        n->left = printDeleteRecurs(nv, n->left, deleted);
    }

    if (nv < n->value)
    {   // Delete from left subtree
        n->right = printDeleteRecurs(nv, n->right, deleted);
    }

    else // nv > n->value
    {   // Delete from right subtree
        n->right = printDeleteRecurs(nv, n->right);
    }
    
    /* Check for height imbalance after deleting */
    
    if (isImbalanced(n) )
    {   // Height imbalance, so rebalance it
        return rebalance(n);
    }

    else    // No height imbalance, so update height and return it
    {
        // Update the height of this node
        updateHeight(n);

        return n;
    }
}

// Returns the new root after rebalancing the tree
// X, Y are determined as the greater-height children or subchildren, respectively, of Z
kAVLTree::Node* kAVLTree::rebalance(Node* n)
{
    Node* newRoot = nullptr;    // Store new root, for readability

    // Get the left and right subtree heights of Z
    int leftHeight = n->left ? n->left->height : -1;
    int rightHeight = n->right ? n->right->height : -1;
    
    // Set Y to child of Z with greater height
    Node* y = leftHeight > rightHeight ? n->left : n->right;    

    // Get the left and right subtree heights of Z
    leftHeight = y->left ? y->left->height : -1;
    rightHeight = y->right ? y->right->height : -1;

    // Set X to child of Y with greater height
    Node* x = leftHeight > rightHeight ? y->left : y->right;

    if (y == n->left)
    {
        if (x == y->left)
        {   // Case 1
            newRoot = rotateCW(n); // Rotate Y, Z clockwise
        }

        else    // x == y->right
        {   // Case 3
            n->left = rotateCounterCW(y);   // Rotate X, Y counter-clockwise
                                            // Now, X is Z's left child
            newRoot = rotateCW(n); // Rotate X, Z clockwise
        }
    }

    else    // y == n->right
    {
        if (x == y->left)
        {   // Case 4
            n->right = rotateCW(y); // Rotate X, Y clockwise
                                    // Now, X is Z's right child
            newRoot = rotateCounterCW(n);  // Rotate X, Z counter-clockwise
        }

        else    // x == y->right
        {   // Case 2
            newRoot = rotateCounterCW(n);    // Rotate Y, Z counter-clockwise
        }
    }

    return newRoot; // Return the new root
}

// Returns the predecessor in a tree
kAVLTree::Node* kAVLTree::getPredecessor(Node* n)
{
    while (n->right)
    {
        n = n->right;
    }
    return n;
}

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
    return std::abs(leftHeight - rightHeight) > k;
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

kAVLTree::NodeVal kAVLTree::NodeVal::abs() const
{
    return NodeVal(std::abs(this->whole), std::abs(this->fract) );
}

// Returns a string of 'whole.fract'
std::string kAVLTree::NodeVal::toString() const
{
    return std::to_string(this->whole) + "." + std::to_string(this->fract);
}
