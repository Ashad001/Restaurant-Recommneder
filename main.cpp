#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class TreeNode
{
public:

    // 1. int column value.. refers to column split on by parent node
    //    null in root's case
    int ColVal;
    // 2. int column split on.. column this node splits on
    //    value doesn't matter if guess is not null
    int ColSplitOn;
    // 3. int guess
    //    null unless node is a leaf case
    int Guess; // On leaf!
    // 4. vector of node pointers called "children"
    //    pointers to all of the children of this node
    //    also doesn't matter if node is base case
    vector<TreeNode *> children;
    // constructor
    TreeNode()
    {
        ColVal = ColSplitOn = Guess = NULL;
    }
};
class DecisionTree
{
public:
    TreeNode *root;
    vector<vector<int>> Data;
    vector<vector<int>> colVals;
    DecisionTree()
    {
        // This Constructor Will Fetch The Data -- OVER @HASEEB   
    }
    
};

void Fit(vector<vector<int>> matrix, vector<vector<int>> label)
{
}

int main(int argc, char const *argv[])
{
    // Started 11/2/22

    return 0;
}
