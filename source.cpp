#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <array>
#include <algorithm>
#include <sstream>
#include <cmath>
using namespace std;
using MATRIX = vector<vector<int>>;

template <class T>
void PrintData1(vector<T> &data)
{
    for (auto num : data)
    {
        cout << num << ", ";
    }
    cout << endl;
}

template <class T>
void PrintData2(vector<vector<T>> &data)
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
bool IsInIt(vector<int> &d, int i)
{
    for (auto n : d)
    {
        if (i == n)
        {
            return true;
        }
    }
    return false;
}

class bestSplitValues
{
public:
    float resEntropy; // Entropy Value for each Node
    int Feature;      // Col in terms of data
    int Category;     // Row in terms of data
};

class TreeNode
{
public:
    MATRIX trainData;
    bestSplitValues bestSplit;

    TreeNode *leftChild;
    TreeNode *rightChild;
    static vector<int> selectedFeature;

    TreeNode(MATRIX &data)
    {
        this->leftChild = this->rightChild = NULL;
        // const vector<int> outputsBefore = data[0]; // Index 0
        this->trainData = data;
        // this->bestSplit = GetBestSplit(data);
    }
    vector<pair<int, int>> CountResults(MATRIX &Data, int index)
    {
        vector<pair<int, int>> vp;
        int count0{0}, count1{0};
        if (index <= 0)
        {
            count0 = count1 = 0;
            for (int i = 0; i < Data.size(); i++)
            {
                count0 += (Data[i][0] == 0) ? 1 : 0;
                count1 += (Data[i][0] == 1) ? 1 : 0;
            }
            vp.push_back({count1, count0});
        }
        else
        {
            map<int, int> countLabels;
            map<int, int> countAll;
            for (int i = 0; i < Data.size(); i++)
            {
                countAll[Data[i][index]]++;
                countLabels[Data[i][index]] += Data[i][0];
            }
            for (auto i = countLabels.begin(), j = countAll.begin(); i != countLabels.end() && j != countAll.end(); i++, j++)
            {
                count1 = i->second;
                count0 = j->second - i->second;
                vp.push_back({count1, count0});
            }
        }
        return vp;
    }
    double EntropyOfCol(pair<int, int> p)
    {
        double total = double(p.first + p.second);
        double ret = -1 * (double(p.first / total) * log2(double(p.first / total))) - 1 * (double(p.second / total) * log2(double(p.second / total)));
        return (isnan(ret)) ? 0 : ret;
    }
    float ColGain(MATRIX &data, int index)
    {
        float TotalColEntropy = EntropyOfCol(CountResults(data, 0)[0]);
        if (index == 0)
        {
            return TotalColEntropy;
        }
        vector<float> cal;
        vector<pair<int, int>> vp = CountResults(data, index);
        for (auto n : vp)
        {
            int total = n.first + n.second;
            float prob = (float)total / data.size();
            cal.push_back(-1 * float(prob) * EntropyOfCol(n));
        }
        float ret = TotalColEntropy;
        for (auto n : cal)
        {
            ret += n;
        }
        return ret;
    }
    pair<int, float> GetInfoGain(MATRIX &data)
    {
        if (data.size() == 0)
        {
            return {-1, 0.0f};
        }
        vector<float> cal;
        map<int, float> calM;
        int maxIndex = -1;

        for (int i = 1; i <= data[0].size(); i++)
        {
            // if (TreeNode::selectedFeature.empty() || !IsInIt(TreeNode::selectedFeature, i))
            // {
            calM[i] = ColGain(data, i);
            // }
        }

        float MaxRet = 0.f;
        for (auto n : calM)
        {
            if (n.second > MaxRet)
            {
                MaxRet = n.second;
                maxIndex = n.first;
            }
        }
        selectedFeature.push_back(maxIndex);
        return {maxIndex, MaxRet};
    }
    vector<int> GetColumn(MATRIX &dataT, int col)
    {
        vector<int> ret;
        for (int i = 0; i < dataT.size(); i++)
        {
            ret.push_back(dataT[i][col]);
        }
        return ret;
    }
};
vector<int> TreeNode::selectedFeature;

bool isIdentical(string c, vector<string> &alreadyE)
{
    for (auto n : alreadyE)
    {
        if (c == n)
            return true;
    }
    alreadyE.push_back(c);
    return false;
}
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
MATRIX Bit_Mask(vector<vector<string>> &data)
{
    // Converting string data to integers (AKA masking)
    MATRIX cvt(data.size(), vector<int>(data[0].size() - 1, 0));
    int index = 1; // First Two Cols not necessary here
    int row = 0, col = 0;

    for (index = 1; index < data[0].size(); index++)
    {
        row = 0;
        int val = 0;
        vector<string> temp;
        map<string, int> mp;
        for (int i = 0; i < data.size(); i++)
        {
            if (isIdentical(data[i][index], temp) == 0)
            {
                mp[data[i][index]] = i;
            }
            cvt[row][col] = mp[data[i][index]];
            row++;
        }
        col++; // next Col
    }
    return cvt;
}
bool remove_column(MATRIX &a, int pos)
{
    bool success = pos < a[0].size();

    if (success)
    {
        MATRIX temp(a.size(), vector<int>(a[0].size() - 1, 0));
        vector<int> temp2;
        for (int i = 0; i < a.size(); i++)
        {
            cout << "fhdsf";
            for (int j = 0; j < a[0].size(); i++)
            {
                if (j != pos - 1)
                    temp2.push_back(a[i][j]);
            }
            temp.push_back(temp2);
        }
        a.clear();
        a.resize(temp.size(), vector<int>(temp[0].size() - 1));
        for (int i = 0; i < temp.size(); i++)
        {
            a.push_back(temp[i]);
        }
    }
    return success;
}

class TwoMatrix
{
public:
    MATRIX accepted;
    MATRIX rejected;
};

class DecisionTree
{
public:
    TreeNode *root;
    vector<vector<string>> DataInString;
    DecisionTree(string filename)
    {
        // This Constructor Will Fetch The Data and convert to integers
        this->DataInString = RETRIEVE_DATA(filename);
        MATRIX DataForTraining = Bit_Mask(DataInString);
        TreeNode *rootC = new TreeNode(DataForTraining);
        // ConstructTree(root);
        this->root = rootC;
    }
    TwoMatrix Split_Data(MATRIX &tempData, int f)
    {
        MATRIX Accepted;
        MATRIX Rejected;
        for (int i = 0; i < tempData.size(); i++)
        {
            if (tempData[i][f] == 1)
            {
                Accepted.push_back(tempData[i]);
            }
            else
            {
                Rejected.push_back(tempData[i]);
            }
        }
        TwoMatrix tw;
        if (remove_column(Accepted, f) && remove_column(Rejected, f))
        {
            tw.accepted = Accepted;
            tw.rejected = Rejected;
        }
        else
        {
            tw.accepted.clear();
            tw.rejected.clear();
        }
        return tw;
    }
};

int main(int argc, char const *argv[])
{
    DecisionTree DT("TEMP.csv");
    // bestSplitValues b = DT.root->bestSplit;
    // cout << b.resEntropy << ", " << b.Feature << ", " << b.Category << endl;
    // cout << DT.root->ColGain(DT.root->trainData, 4);
    // cout << DT.root->GetInfoGain(DT.root->trainData).second;
    // vector<pair<int, int>> v = DT.root->CountResults(DT.root->trainData, 1);
    // for (auto n : v)
    // {
    //     cout << DT.root->ColGain(n) << endl;
    //     // cout << n.first << ", " << n.second << endl;
    // }
    pair<int, float> fd = DT.root->GetInfoGain(DT.root->trainData);
    cout << DT.root->GetInfoGain(DT.root->trainData).first << ", " << DT.root->GetInfoGain(DT.root->trainData).second << " ..." << endl;

    TwoMatrix newD = DT.Split_Data(DT.root->trainData, fd.first);
    PrintData2(newD.accepted);
    cout << DT.root->GetInfoGain(newD.accepted).first << ", " << DT.root->GetInfoGain(newD.accepted).second << " ..." << endl;
    // cout << DT.root->GetInfoGain(DT.root->trainData).first << ", " << DT.root->GetInfoGain(DT.root->trainData).second << " ..." << endl;
    // cout <<  DT.root->ColGain(DT.root->trainData, 0);
}
