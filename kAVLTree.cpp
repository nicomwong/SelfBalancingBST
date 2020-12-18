// kAVLTree.cpp

#include "kAVLTree.h"

#include <iostream>
#include <string>
#include <queue>

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
// Insert is the same as in BSTs
// Self-balancing is done by walking up to the root, finding the first node where the AVL height property is broken
//  Then, a single- or double- rotation is performed to rebalance
//  ??? This is recursively done upwards (toward the root)
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

    // TO-DO: Implement Second part (below)
    /*  Second:
     *      Update the height of this node
     *      Check if the height property has been broken
     *          If it has been broken, then perform single- or double- rotation to rebalance
    */
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
kAVLTree::Node::Node(int whole, int fract) : height(-1), value(whole, fract)
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
    return this->whole + "." + this->fract;
}
