#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
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
        ColVal = ColSplitOn = Guess = 0;
    }
};
vector<vector<string>> RETRIEVE_DATA(string filename)
{
    // Code For Converting .csv data to strings (vector:2D)
    vector<vector<string>> record;
    vector<string> row;
    string line, data;

    fstream file(filename, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();

            stringstream s(line);
            while (getline(s, data, ','))
            {
                row.push_back(data);
            }
            record.push_back(row);
        }
    }
    else
    {
        cout << "Could not Open file";
    }
    return record;
}
vector<vector<int>> Bit_Mask(vector<vector<string>> &data)
{
    // Converting string data to integers (AKA masking)
    vector<vector<int>> cvt(data.size(), vector<int>(data[0].size() - 2, 0));
    int index = 2; // First Two Cols not necessary here
    int row = 0, col = 0;
    map<string, int> mp;

    for (index = 2; index < data[0].size(); index += 1)
    {
        row = 0;
        mp.clear();
        for (int i = 0; i < data.size(); i++)
        {
            mp[data[i][index]]++;
        }
        for (int i = 0; i < data.size(); i++)
        {
            cvt[row][col] = mp[data[i][index]] % 4;
            row++;
        }
        col++;
    }
    return cvt;
}

class DecisionTree
{
public:
    TreeNode *root;
    vector<vector<int>> Data;
    // vector<vector<int>> colVals;
    DecisionTree(string filename)
    {
        // This Constructor Will Fetch The Data -- OVER @HASEEB
        vector<vector<string>> s = RETRIEVE_DATA(filename);
        this->Data = Bit_Mask(s);
    }
};

template <class T>
void PrintData(vector<vector<T>> &data)
{
    for (auto row : data)
    {
        for (auto num : row)
        {
            cout << num << ", ";
        }
        cout << endl;
    }
}

int main(int argc, char const *argv[])
{
    // Started 11/2/22
    DecisionTree DT("DS-data.csv");
    // DT.Bit_Mask(DT.Data);
    PrintData<int>(DT.Data);

    return 0;
}
