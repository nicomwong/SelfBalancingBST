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

class kAVLTree
{
public:
    kAVLTree(int k);    // Constructs kAVLTree with parameter k

    void printInsert(int whole, int frac); // Prints "'whole.frac' inserted" if it was not previously in the tree

private:
    struct Node
    {
        int whole, fract;   // Single-precision decimal value
        int height;         // Current height of this node
        Node* left, right;  // Left and right children
    };

    Node* root;
    int k;

    Node* printInsertRecurs(int whole, int frac, Node* n); // Recursive helper for printInsert; returns new root after insertion and self-balancing

    Node* createNode(int whole, int frac);  // Returns a newly-created node with parameter values
};

#endif