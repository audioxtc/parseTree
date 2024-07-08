#include <iostream>
#include <string>
#include "ParseTree.h"

using namespace std;

int main() {

    ParseTree testTree;
    testTree.readFile();
    testTree.buildTree();
    testTree.evaluate();
    return 0;
}