#ifndef KAVLTREE_H
#define KAVLTREE_H

// Nicholas M Wong
// 11.23.2020

// This is a k-AVLTree
// It is a self-balancing binary tree with the following properties:
//  1. value(left child) <= value(parent) <= value(right child)
//  2. |height(left child) - height(right child)| <= k

#include <iostream>
#include <vector>
#include <string>
#include <queue>

class kAVLTree
{
public:
    kAVLTree(int k);    // Constructs kAVLTree with parameter k

    void printInsert(int whole, int frac);  // Prints "'whole.frac' inserted" if it was not previously in the tree
    void printDelete(int whole, int frac);  // Prints "'whole.frac' deleted" if it was deleted
    void printSearch(int whole, int frac) const;  // Prints "'whole.frac' found" if it is in the tree
    void printApproxSearch(int whole, int frac) const;  // Prints "closest to 'whole.frac' is 'closest_whole.closest_frac'" 
    void printInOrder() const;    // Prints the node values in-order
    void printPreOrder() const;   // Prints the node values pre-order

private:
    struct NodeVal  // Stores single-precision decimal that supports comparison
    {
        NodeVal(int whole, int fract);  // Parameterized constructor
        
        NodeVal& operator=(NodeVal const& other);    // Overloaded assignment operator

        bool operator==(NodeVal const& other) const;  // Overloaded equality operator
        bool operator<(NodeVal const& other) const;   // Overloaded less than operator
        bool operator>(NodeVal const& other) const;   // Overloaded greater than operator

        NodeVal operator-(NodeVal const& other) const;  // Overloaded subtraction operator

        NodeVal abs() const; // Returns the absolute value of this NodeVal

        std::string toString() const; // Returns a string of 'whole.fract'
        
        int whole, fract;
    };

    struct Node
    {
        Node(int whole, int fract); // Parameterized constructor

        NodeVal value;  // Single-precision decimal value
        int height;     // Current height of this node
        Node* left;     // Left child
        Node* right;    // Right child
    };

    Node* root;
    int k;

    Node* printInsertRecurs(NodeVal const& nv, Node* n); // Recursive helper for printInsert; returns new root after insertion and self-balancing
    Node* printDeleteRecurs(NodeVal const& nv, Node* n, bool& deleted); // Recursive helper for printDelete; returns new root after deletion and self-balancing
    std::string printInOrderRecurs(Node* n) const;    // Recursive helper for printInOrder; returns string of values in-order, space-separated
	std::string printPreOrderRecurs(Node* n) const;	// Recursive helper for printPreOrder; returns a string of values pre-order, space-separated

    Node* rebalance(Node* n);   // Returns the new root after rebalancing the tree
    Node* getPredecessor(Node* n);   // Returns the predecessor in a tree
    Node* rotateCW(Node* n);    // Helper for printInsertRecurs; returns new root after rotating the left child and the current node clockwise
    Node* rotateCounterCW(Node* n); // Helper for printInsertRecurs; returns new root after rotating the right child and the current node counter-clockwise
    void updateHeight(Node* n); // Updates the height of the given node
    bool isImbalanced(Node* n) const; // Returns true iff a height imbalance is seen at the given node
    Node* createNode(int whole, int frac) const;  // Returns a newly-created node with input parameter values
};

#endif
