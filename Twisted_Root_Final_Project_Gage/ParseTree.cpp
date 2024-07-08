//
// Created by Jeremy Gage on 5/11/20.
//

#include "ParseTree.h"

//CONSTRUCTORS
ParseTree::ParseTree() : rootPtr(NULL)
{

}  // end default constructor

ParseTree::ParseTree( string& rootItem)
{
    rootPtr = new BinaryNode(rootItem, NULL, NULL);
    ifstream equations;
    equations.open("equations.txt");
    if (equations.fail())
    {
        std::cout << "File opening failed.\n";
        exit(1);
    }
    std::string str;
    equations>>str;
    line.push_back(str);
    inFixExp=str;
    cout << inFixExp;
    cout << str << "\n";
    cout << "File has been read into vector.\n";
    equations.close();
}  // end constructor

//HELPER FUNCTIONS

BinaryNode* ParseTree::insertInorder(BinaryNode* subTreePtr, BinaryNode* newNodePtr) {
    if (subTreePtr == NULL)
        return newNodePtr;
    else {
        if (subTreePtr->getItem() > newNodePtr->getItem()){
            subTreePtr->setLeftChildPtr(insertInorder(subTreePtr->getLeftChildPtr(), newNodePtr));
        } else {
            subTreePtr->setRightChildPtr(insertInorder(subTreePtr->getRightChildPtr(), newNodePtr));
        }
        return subTreePtr;
    }  // end else
}  // end insertInorder

BinaryNode* ParseTree :: findNode(BinaryNode* subTreePtr,  string& target)  {
    if (subTreePtr == nullptr)
        return nullptr;                                           // Not found
    else if (subTreePtr->getItem() == target)
        return subTreePtr;                                  // Found
    else if (subTreePtr->getItem() > target) {
        // Search left subtree
        return findNode(subTreePtr->getLeftChildPtr(), target);
    }
}

string ParseTree::getEntry( string& anEntry) // throw(NotFoundException)
{
    BinaryNode* nodeWithEntry = findNode(rootPtr, anEntry);
    if (nodeWithEntry == NULL){
        cout << "Entry not found in tree." << endl;
        //throw NotFoundException("Entry not found in tree.");
    } // else
    return nodeWithEntry->getItem();
}  // end getEntry



auto ParseTree::printItem(string anEntry)
{
    std::cout << getEntry(anEntry);
}

void ParseTree::readFile() {
    {
        ifstream equations;
        equations.open("equations.txt");
        if (equations.fail()) {
            std::cout << "File opening failed.\n";
            exit(1);
        }
        std::string str;
        equations >> str;
        line.push_back(str);
        inFixExp = str;
        //cout << inFixExp;
        cout << str << "\n";
        cout << "File has been read into vector.\n";
        equations.close();
    }
}

string ParseTree::getRootData()  //throw(PrecondViolatedExcep)
{
    if (isEmpty())
        cout << "getRootData() called with empty tree." << endl;
    //throw PrecondViolatedExcep("getRootData() called with empty tree.");

    return rootPtr->getItem();
}

bool ParseTree::isEmpty()
{
    return rootPtr == NULL;
}  // end isEmpty

bool ParseTree::createNewRightNode()
{
    BinaryNode* right=new BinaryNode;//=new BinaryNode;//create a new node
    BinaryNode* currentNodePtr; //create a new temp pointer to assign to pointer in top of stack
    currentNodePtr = ptrStack.top();//assign this node to the top pointer in the stack
    currentNodePtr->setRightChildPtr(right); //set current node right child pointer to this new node
    ptrStack.push(right); //push the current node pointer on to the stack
    return true;
}

bool ParseTree::setOperatorNode(string aCh)
{
    bool set;
    BinaryNode* opPtr;
    opPtr=ptrStack.top();//get pointer to current node off of stack
    opPtr->setItem(aCh);
    set = true;
    return set;
}

bool ParseTree::setOperand(string aToken)
{
    bool ok = false;
    BinaryNode* tempNode;
    tempNode=ptrStack.top();
    tempNode->setItem(aToken);
    ok=true;
    return ok;
}

bool ParseTree::createNewLeftNode()
{
    bool done = false;
    BinaryNode* left = new BinaryNode;

    if (!ptrStack.empty()) {//if pointer stack is not empty
        //peek the stack and set its leftchild pointer to the new node
        BinaryNode* currentNodePtr;
        currentNodePtr=ptrStack.top();
        currentNodePtr->setLeftChildPtr(left);
        ptrStack.push(currentNodePtr->getLeftChildPtr());//push the pointer to the left child to the stack
        done = true;
    }

    else //tree is empty or stack is empty or both
    {
        BinaryNode* currentNodePtr =new BinaryNode;
        rootPtr=currentNodePtr;
        ptrStack.push(rootPtr);
        currentNodePtr->setLeftChildPtr(left);
        ptrStack.push(left); //push the new pointer to the stack (current node pointer)
        done = true;
    }
    return done;
};

void ParseTree::buildTree() { //builds tree with expression read in from file "equations.txt"
    std::stringstream infix(inFixExp);
    char token;
    int partial;
    string tokenStr;
    bool flag=false;
    while (infix >> token) {
        if (token == '(') //create new node and descend, stack is updated with pointer to new node
        {
            createNewLeftNode();
            flag = false;
        }
        else if (token == '-' || token == '+' || token == '*' ||
            token == '/')//sets root value of current node to the operator value
        {
            tokenStr = string(1,token);
            setOperatorNode(tokenStr);
            createNewRightNode();//<< "[1, true. 0, false]\n";
            flag=false;
        }
        else if (token == ')') {
            if (!ptrStack.empty())
                ptrStack.pop();
        }
        else//operand case
        {
            if (!flag && !isdigit(infix.peek()))//single digit case
            {
                tokenStr = string(1, token);
                setOperand(tokenStr);
                ptrStack.pop();}

            if (flag && isdigit(infix.peek()))
            {
                tokenStr = tokenStr + string(1, token);; //concatenate
                flag=true;

            }
            if (!flag && isdigit(infix.peek()))//multi-digit, first digit case
            {
                tokenStr=string(1, token);
                flag=true;
            }


            if (flag && !isdigit(infix.peek()))//multi-digit case, second+ digit case
            {
                tokenStr=tokenStr+string(1, token);
                setOperand(tokenStr);
                ptrStack.pop();
                flag=false;
            }
        }
    }
}

int ParseTree::evaluateNode(BinaryNode* treePtr) {
    if (!treePtr)
        return 0;

    if (!treePtr->getLeftChildPtr() && !treePtr->getRightChildPtr())
        return toInt(treePtr->getItem());

    int left_val = evaluateNode(treePtr->getLeftChildPtr());

    int right_val = evaluateNode(treePtr->getRightChildPtr());

    if (treePtr->getItem() == "+")
        return left_val + right_val;

    if (treePtr->getItem() == "-")
        return left_val - right_val;

    if (treePtr->getItem() == "*")
        return left_val * right_val;

    if (treePtr->getItem() == "/")
        return left_val / right_val;
}

//PUBLIC FUNCTIONS

//Evaluate function calls evaluateNode(BinaryNode*)
//base case rootPtr=nullptr;
//go to rootPtr
//check for left most leaf, then check for right most leaf then evaluate using operator stored in parent node
//store each node pointer in a stack
//go down left side of tree to a leaf
//if node is a leaf store left child's value in a variable
//go up one level and store the operator
//go to the right child and check for a leaf
//if a leaf then store value in right child and repeat until base case

void ParseTree::evaluate()
{
    cout << "calling evaluate...";
    cout<<evaluateNode(rootPtr);

} // end evaluate

int ParseTree::toInt(string aString) {
    int num = 0;
        // Check if the integral value is
        // negative or not
        // If it is not negative, generate the number
        // normally
        if(aString[0]!='-')
            for (int i=0; i<aString.length(); i++)
                num = num*10 + (int(aString[i])-48);
            // If it is negative, calculate positive number
            // first ignoring the sign and invert the
            // sign at the end
        else
            for (int i=1; i<aString.length(); i++)
            {
                num = num*10 + (int(aString[i])-48);
                num = num*-1;
            }
        return num;
}

void ParseTree::setRootData( string& newItem)
{
    if (isEmpty())
        rootPtr = new BinaryNode(newItem, nullptr, nullptr);
    else
        rootPtr->setItem(newItem);
} // end setRootData
