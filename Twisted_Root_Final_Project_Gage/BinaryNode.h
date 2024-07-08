//
// Created by Jeremy Gage on 5/11/20.
//

#ifndef FINAL_PROJECT_MAY_11_VERSION_BINARYNODE_H
#define FINAL_PROJECT_MAY_11_VERSION_BINARYNODE_H


//
// Created by Jeremy Gage on 5/5/20.
//

#ifndef BST_BINNODE_HPP
#define BST_BINNODE_HPP

#include <cstddef>
#include <string>

using namespace std;
//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** A class of nodes for a link-based binary tree.
 * Listing 16-2.
  @file BinaryNode.h */

class BinaryNode
{
private:
    string              item;           // Data portion
    BinaryNode* leftChildPtr;   // Pointer to left child
    BinaryNode* rightChildPtr;  // Pointer to right child

public:
    BinaryNode();
    BinaryNode(string& anItem);
    BinaryNode( string& anItem, BinaryNode* leftPtr, BinaryNode* rightPtr);

    void setItem(string& anItem);
    string getItem() ;

    bool isLeaf() ;
    BinaryNode* getLeftChildPtr() ;
    BinaryNode* getRightChildPtr() ;

    void setLeftChildPtr(BinaryNode* leftPtr);
    void setRightChildPtr(BinaryNode* rightPtr);
}; // end BinaryNode

#endif //BST_BINNODE_HPP





#endif //FINAL_PROJECT_MAY_11_VERSION_BINARYNODE_H
