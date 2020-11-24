// kAVLTree.cpp

#include <iostream>

// Constructs a k-AVLTree with parameter k
kAVLTree::kAVLTree(int k) : k(k), root(nullptr)
{}

// Inserts node with value 'whole.frac' if it was not previously in the tree
// Prints "'whole.frac' inserted" if it was inserted
void kAVLTree::printInsert(int whole, int frac)
{
    this->root = printInsertRecurs(whole, frac, this->root);
}

// Recursive helper for printInsert
// Returns a pointer to the new root of the subtree after inserting and self-balancing
// Insert is the same as in BSTs
// Self-balancing is done by walking up to the root, finding the first node where the AVL height property is broken
//  Then, a single- or double- rotation is performed to rebalance
//  ??? This is recursively done upwards (toward the root)
Node* kAVLTree::printInsertRecurs(int whole, int frac, Node* n)
{
    /* First, insert the node and print so (if it does not already exist) */

    if (n == nullptr)
    {   // Reached end, so insert, print, and return
        std::cout << whole << "." << frac << " inserted" << std::endl;
        return createNode(whole, frac);
    }

    if (whole == n->whole && frac == n->frac)
    {   // Node already exists, so do nothing and return
        return n;
    }

    if (whole < n->whole)
    {   // Insert into left subtree
        n->left = printInsertRecurs(whole, frac, n->left);
    }

    else if (whole > n->whole)
    {   // Insert into right subtree
        n->right = printInsertRecurs(whole, frac, n->right);
    }

    else // whole == n->whole
    {
        if (frac < n->frac)
        {   // Insert into left subtree
            n->left = printInsertRecurs(whole, frac, n->left);
        }

        else // frac > n->frac
        {   // Insert into right subtree
            n->right = printInsertRecurs(whole, frac, n->right);
        }
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
    Node* n = new Node;
    n->whole = whole;
    n->frac = frac;
    return n;
}