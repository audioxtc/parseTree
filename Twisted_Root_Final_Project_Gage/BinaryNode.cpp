//
// Created by Jeremy Gage on 5/11/20.
//

#include "BinaryNode.h"

BinaryNode::BinaryNode()
{
    //item = NULL;
    leftChildPtr = NULL;
    rightChildPtr = NULL;
}  // end default constructor

BinaryNode::BinaryNode(string& anItem) : item(anItem), leftChildPtr(NULL), rightChildPtr(NULL)
{
}  // end constructor

BinaryNode::BinaryNode(string& anItem, BinaryNode* leftPtr, BinaryNode* rightPtr) : item(anItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr)
{
}  // end constructor

void BinaryNode::setItem( string& anItem)
{
    item = anItem;
}  // end setItem

string BinaryNode::getItem()
{
    return item;
}  // end getItem

bool BinaryNode::isLeaf()
{
    return ((leftChildPtr == NULL) && (rightChildPtr == NULL));
}

void BinaryNode::setLeftChildPtr(BinaryNode* leftPtr)
{
    leftChildPtr = leftPtr;
}  // end setLeftChildPtr

void BinaryNode::setRightChildPtr(BinaryNode* rightPtr)
{
    rightChildPtr = rightPtr;
}  // end setRightChildPtr


BinaryNode* BinaryNode::getLeftChildPtr()
{
    return leftChildPtr;
}  // end getLeftChildPtr

BinaryNode* BinaryNode::getRightChildPtr()
{
    return rightChildPtr;
}  // end getRightChildPtr

