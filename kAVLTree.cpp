// kAVLTree.cpp

#include "kAVLTree.h"

#include <iostream>

// Constructs a k-AVLTree with parameter k
kAVLTree::kAVLTree(int k) : k(k), root(nullptr)
{}

// Inserts node with value 'whole.frac' if it was not previously in the tree
// Prints "'whole.frac' inserted" if it was inserted
void kAVLTree::printInsert(int whole, int frac)
{
    NodeVal val(whole, frac);
    this->root = printInsertRecurs(val, this->root);
}

// Prints "'whole.frac' found" if it is in the tree
void kAVLTree::printSearch(int whole, int frac)
{
    NodeVal nv(whole, frac);

    Node* n = this->root;
    while (n)
    {
        if (nv < n->value)
        {
            n = n->left;
        }

        else if (nv > n->value)
        {
            n = n->right;
        }

        else // nv == n->value
        {
            std::cout << nv << " found" << std::endl;
            return;
        }
    }
    
    // Now, n == nullptr, so the node is not in the tree
    std::cout << nv << " not found" << std::endl;
}

// Recursive helper for printInsert
// Returns a pointer to the new root of the subtree after inserting and self-balancing
// Insert is the same as in BSTs
// Self-balancing is done by walking up to the root, finding the first node where the AVL height property is broken
//  Then, a single- or double- rotation is performed to rebalance
//  ??? This is recursively done upwards (toward the root)
Node* kAVLTree::printInsertRecurs(NodeVal const& nv, Node* n)
{
    /* First, insert the node and print so (if it does not already exist) */

    if (n == nullptr)
    {   // Reached end, so insert, print, and return
        std::cout << whole << "." << frac << " inserted" << std::endl;
        return createNode(whole, frac);
    }

    if (nv == n->value)
    {   // Node already exists, so do nothing and return
        return n;
    }

    if (nv < n->value)
    {   // Insert into left subtree
        n->left = printInsertRecurs(whole, frac, n->left);
    }

    else // nv > n->value
    {   // Insert into right subtree
        n->right = printInsertRecurs(whole, frac, n->right);
    }

    // TO-DO: Implement Second part (below)
    /*  Second:
     *      Update the height of this node
     *      Check if the height property has been broken
     *          If it has been broken, then perform single- or double- rotation to rebalance
    */
}

Node* kAVLTree::createNode(int whole, int frac)
{
    Node* n = new Node;     // Create node on heap
    n->value(whole, frac);  // Put in contents
    return n;
}

/* START: NodeVal member functions */

// Default constructor
NodeVal::NodeVal() : whole(-1), fract(0)
{}

// Parameterized constructor
NodeVal::NodeVal(int whole, int fract) : whole(whole), fract(fract)
{}

// Overloaded assignment operator
NodeVal NodeVal::operator=(NodeVal const& other)
{
    this->whole = other.whole;
    this->fract = other.fract;
}

// Overloaded equality operator
bool NodeVal::operator==(NodeVal const& other)
{
    return this->whole == other.whole && this->fract == other.fract;
}

// Overloaded less than operator
bool NodeVal::operator<(NodeVal const& other)
{
    return this->whole < other.whole || (this->whole == other.whole && this->fract < other.fract);
}

// Overloaded greater than operator
bool NodeVal::operator>(NodeVal const& other)
{
    return this->whole > other.whole || (this->whole == other.whole && this->fract > other.fract);
}