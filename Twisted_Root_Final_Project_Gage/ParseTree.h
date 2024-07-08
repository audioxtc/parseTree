//
// Created by Jeremy Gage on 5/11/20.
//

#ifndef FINAL_PROJECT_MAY_11_VERSION_PARSETREE_H
#define FINAL_PROJECT_MAY_11_VERSION_PARSETREE_H


#include "BinaryNode.h"
#include <string>
#include <stack>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
//#include<bits/stdc++.h>

using std::cout;

class ParseTree : public BinaryNode
{

private:

    BinaryNode* rootPtr;
    std::string inFixExp;
    vector<string> line;
    stack<BinaryNode *> ptrStack;
    stack<string> evalStack;
    stack<int> operandStack;
    stack<char> operatorStack;

protected:
    BinaryNode* insertInorder(BinaryNode* subTreePtr, BinaryNode* newNodePtr);
    BinaryNode* postorder(BinaryNode* treePtr);
    string getEntry( string& anEntry) ;
    BinaryNode* findNode(BinaryNode* treePtr,  string& target) ;
    auto printItem(string anEntry);
    int evaluateNode(BinaryNode* treeePtr);

public:
    ParseTree();
    ParseTree( string& rootItem);
    void buildTree();
    BinaryNode* newNode(string anItem);
    bool createNewLeftNode();
    void postorderTraverseAndDisplay();
    string getRootData() ;
    bool isEmpty() ;
    void readFile();
    bool createNewRightNode();
    bool setOperatorNode(string aCh);
    bool setOperand(string aToken);
    void inorder(BinaryNode*);
    void setRootData(string& newItem);
    BinaryNode* findNextLeft(BinaryNode* subTreePtr);
    char findSuccessorValue(BinaryNode* subTreePtr);
    void evaluate();
    int toInt(string aStr);
};


#endif //FINAL_PROJECT_MAY_11_VERSION_PARSETREE_H
