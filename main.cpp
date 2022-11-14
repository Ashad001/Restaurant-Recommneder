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
    vector<vector<string>> record;
    vector<string> row;
    string line, data;

    fstream file("DS-data.csv", ios::in);
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
        // for (int i = 0; i < record.size(); i++)
        // {
        //     for (int j = 0; j < record[i].size(); j++)
        //     {
        //         cout << record[i][j] << " ";
        //     }
        //     cout << endl;
        // }
    }
    else
    {
        cout << "Could not Open file";
    }
    return record;
}
bool alreadyExist(string c, vector<string> ch)
{
    for (auto x : ch)
    {
        if (x == c)
        {
            return true;
        }
    }
    return false;
}

class DecisionTree
{
public:
    TreeNode *root;
    vector<vector<string>> Data;
    vector<vector<int>> colVals;
    DecisionTree(string filename)
    {
        // This Constructor Will Fetch The Data -- OVER @HASEEB
        this->Data = RETRIEVE_DATA(filename);
    }
    vector<vector<int>> Bit_Mask(vector<vector<string>> &data)
    {
        vector<vector<int>> cvt(data.size(), vector<int>(data[0].size() - 2, 0));
        vector<string> alreadyEx;
        int index = 2;
        int row = 0, col = 0;
        map<string, int> mp;

        for (index = 2; index < data[0].size(); index += 1)
        {
            row = 0;
            alreadyEx.clear();
            mp.clear();
            for (int i = 0; i < data.size(); i++)
            {
                mp[data[i][index]]++;
            }
            for (int i = 0; i < data.size(); i++)
            {
                if (alreadyExist(data[i][index], alreadyEx) == 0)
                {
                    alreadyEx.push_back(data[i][index]);
                }
                cvt[row][col] = mp[data[i][index]] % 4;
                row++;
            }
            col++;
        }
        return cvt;
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
    DT.Bit_Mask(DT.Data);
    vector<vector<int>> ans = DT.Bit_Mask(DT.Data);
    PrintData<int>(ans);

    return 0;
}
