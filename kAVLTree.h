#ifndef KAVLTREE_H
#define KAVLTREE_H

// Nicholas M Wong
// 11.23.2020

// This is a k-AVLTree
// It is a self-balancing binary tree with thegit add following properties:
//  1. value(left child) <= value(parent) <= value(right child)
//  2. |height(left child) - height(right child)| <= k

#include <iostream>
#include <vector>
#include <string>

class kAVLTree
{
public:
    kAVLTree(int k);    // Constructs kAVLTree with parameter k

    void printInsert(int whole, int frac);  // Prints "'whole.frac' inserted" if it was not previously in the tree
    void printSearch(int whole, int frac);  // Prints "'whole.frac' found" if it is in the tree
    void printInOrder();    // Prints the node values in-order

private:
    struct NodeVal  // Stores single-precision decimal that supports comparison
    {
        NodeVal();  // Default constructor
        NodeVal(int whole, int fract);  // Parameterized constructor
        
        NodeVal NodeVal::operator=(NodeVal const& other);    // Overloaded assignment operator

        bool NodeVal::operator==(NodeVal const& other);  // Overloaded equality operator
        bool NodeVal::operator<(NodeVal const& other);   // Overloaded less than operator
        bool NodeVal::operator>(NodeVal const& other);   // Overloaded greater than operator

        friend std::ostream& operator<<(std::ostream& out, NodeVal const& nv);  // Overloaded ostream insertion operator

        int whole, fract;
    };
    
    struct Node
    {
        NodeVal value;      // Single-precision decimal value
        int height;         // Current height of this node
        Node* left, right;  // Left and right children
    };

    Node* root;
    int k;

    Node* printInsertRecurs(NodeVal const& nv, Node* n); // Recursive helper for printInsert; returns new root after insertion and self-balancing
    std::string printInOrderRecurs(Node* n);    // Recursive helper for printInOrder; returns string of values in-order, space-separated

    Node* createNode(int whole, int frac);  // Returns a newly-created node with parameter values
};

#endif