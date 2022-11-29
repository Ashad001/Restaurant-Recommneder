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
using DataFrame = vector<vector<int>>;

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
vector<pair<int, int>> CountResults(DataFrame &Data, vector<int> &results, int index)
{
    vector<pair<int, int>> vp;
    int count0{0}, count1{0};
    if (index < 0)
    {
        for (int i = 0; i < results.size(); i++)
        {
            count0 += (results[i] == 0) ? 1 : 0;
            count1 += (results[i] == 1) ? 1 : 0;
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
            countLabels[Data[i][index]] += results[i];
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
double ColGain(DataFrame &data, int index)
{
    double TotalColEntropy = EntropyOfCol(CountResults(data, data[0], -1)[0]);
    vector<double> cal;
    vector<pair<int, int>> vp = CountResults(data, data[0], index);
    for (auto n : vp)
    {
        int total = n.first + n.second;
        double prob = (double)total / data.size();
        cal.push_back(-1 * double(prob) * EntropyOfCol(n));
    }
    double ret = TotalColEntropy;
    for (auto n : cal)
    {
        ret += n;
    }
    return ret;
}
double GetInfoGain(DataFrame &data)
{
    if (data.size() == 0)
    {
        return 0.0;
    }
    vector<double> cal;
    for (int i = 0; i <= 4; i++)
    {
        cal.push_back(ColGain(data, i));
    }
    double MaxRet = 0.f;
    for (auto n : cal)
    {
        MaxRet = max(MaxRet, n);
    }
    return MaxRet;
}
vector<int> GetColumn(DataFrame &dataT, int col)
{
    vector<int> ret;
    for (int i = 0; i < dataT.size(); i++)
    {
        ret.push_back(dataT[i][col]);
    }
    return ret;
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
    DataFrame trainData;
    bestSplitValues bestSplit;

    TreeNode *leftChild;
    TreeNode *rightChild;

    TreeNode(DataFrame &data)
    {
        this->leftChild = this->rightChild = NULL;
        const vector<int> outputsBefore = data[0]; // Index 0
        this->trainData = data;
        this->bestSplit = GetBestSplit(data);
    }
    float GetEntropy(vector<int> &outcomes)
    {
        if (outcomes.size() == 0)
        {
            return 0.0; // so that it doesn't divide by zero
        }
        return EntropyOfCol(CountResults(trainData, outcomes, -1)[0]);
    }
    static float GetGini(vector<int> &targets)
    {
        if (targets.size() == 0)
        {
            return 0.0;
        }
        float giniSum = 0;
        int count = 0;
        for (int i = 0; i < targets.size(); i++)
        {
            int j;
            for (j = 0; j < i; j++)
                if (targets[i] == targets[j])
                    break;
            if (i == j)
                count++;
        }
        vector<int> counts(count + 1, 0);
        for (auto i : targets)
        {
            counts[i]++;
        }
        for (int i = 0; i < count; i++)
        {
            float div = (float)counts[i] / float(targets.size());
            giniSum += div * (1 - div);
        }
        return giniSum;
    }
    static DataFrame GetSplitTargets(DataFrame &dataT, int feature, int category)
    {
        vector<int> trueSplit;
        vector<int> falseSplit;
        int idx = 0;
        for (auto i : dataT[feature])
        {
            // cout << i << endl;
            int val = dataT[feature][idx];
            if (val == category)
            {
                trueSplit.push_back(idx);
            }
            else
            {
                falseSplit.push_back(idx);
            }
            idx++;
        }
        vector<int> allOutcomes = dataT[0]; // Outcomes/Results/Targets...
        vector<int> falseOutComes;
        vector<int> trueOutcomes;
        for (auto i : trueSplit)
        {
            trueSplit.push_back(allOutcomes[i]);
        }
        for (auto i : falseSplit)
        {
            falseOutComes.push_back(allOutcomes[i]);
        }
        DataFrame ret{trueOutcomes, falseOutComes};
        return ret;
    }
    static bestSplitValues GetBestSplit(DataFrame &dataT)
    {
        vector<int> outputBef = dataT[0];
        float Entropy = GetGini(outputBef);
        int Features = dataT.at(0).size() - 1;
        bestSplitValues bestChoice; // return value
        bestChoice.resEntropy = Entropy;
        bestChoice.Category = bestChoice.Feature = 0;
        int count{0};
        int max_count = INT_MIN;
        for (int f = 1; f <= Features; f++) // From Reservations to timing of dinner
        {
            count = 0;
            vector<int> featureVec = GetColumn(dataT, f);
            for (int i = 0; i < featureVec.size(); i++)
            {
                int j;
                for (j = 0; j < i; j++)
                    if (featureVec[i] == featureVec[j])
                        break;
                if (i == j)
                    count++;
            }
            for (int c = 0; c < count; c++) // MASLAAAA
            {
                DataFrame split = GetSplitTargets(dataT, f, c);
                float trueEntropy = GetGini(split[0]);
                float weightedTrueEntropy = trueEntropy * split[0].size() / outputBef.size(); /// MASLAAAAA
                float falseEntropy = GetGini(split[1]);
                float weightedFalseEntropy = falseEntropy * split[1].size() / outputBef.size();

                float weightedSum = weightedTrueEntropy + weightedFalseEntropy;

                if (weightedSum < bestChoice.resEntropy)
                {
                    bestChoice.resEntropy = weightedSum;
                    bestChoice.Feature = f;
                    bestChoice.Category = c;
                }
            }
        }
        return bestChoice;
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
DataFrame Bit_Mask(vector<vector<string>> &data)
{
    // Converting string data to integers (AKA masking)
    DataFrame cvt(data.size(), vector<int>(data[0].size() - 1, 0));
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

class TwoDataFrames
{
public:
    DataFrame accepted;
    DataFrame rejected;
};

class DecisionTree
{
public:
    TreeNode *root;
    vector<vector<string>> DataInString;
    vector<int> results;
    // void Split_Data(DataFrame &tempData, int f, int c)
    // {
    //     DataFrame Accepted;
    //     DataFrame Rejected;
    //     for (int i = 0; i < tempData.size(); i++)
    //     {
    //         if (tempData[i][f] == c)
    //         {
    //             Accepted.push_back(tempData[i]);
    //         }
    //         else
    //         {
    //             Rejected.push_back(tempData[i]);
    //         }
    //     }
    // }
    // DataFrame colVals;
    DecisionTree(string filename)
    {
        // This Constructor Will Fetch The Data and convert to integers
        this->DataInString = RETRIEVE_DATA(filename);
        DataFrame DataForTraining = Bit_Mask(DataInString);
        TreeNode *rootC = new TreeNode(DataForTraining);
        for (int i = 0; i < DataInString.size(); i++)
        {
            results.push_back(stoi(DataInString[i][1]));
        }
        ConstructTree(root);
        this->root = root;
    }

    void traverseTree(TreeNode *root)
    {
        if (root == NULL)
        {
            return;
        }
        traverseTree(root->leftChild);
        cout << "(" << root->bestSplit.resEntropy << ", " << root->bestSplit.Feature << ", " << root->bestSplit.Category << " )" << endl;
        traverseTree(root->rightChild);
    }
    static TwoDataFrames splitData(DataFrame &dataBefore, int feature, int category)
    {
        vector<int> presentSplit;
        vector<int> absentSplit;
        int index = 0;
        for (auto i : dataBefore[feature])
        {
            int val = dataBefore[feature][index];
            if (val == category)
            {
                presentSplit.push_back(index);
            }
            else
            {
                absentSplit.push_back(index);
            }
            index++;
        }
        int ROWS = dataBefore.size();
        DataFrame presentData;
        vector<int> tempArr;
        for (int row; row < ROWS; row++)
        {
            int i = 0;
            for (auto col : presentSplit)
            {
                tempArr.push_back(dataBefore[row][col]);
                i++;
            }
            presentData.push_back(tempArr);
            tempArr.clear();
        }
        DataFrame absentData;
        for (int row; row < ROWS; row++)
        {
            int i = 0;
            for (auto col : absentSplit)
            {
                tempArr.push_back(dataBefore[row][col]);
                i++;
            }
            absentData.push_back(tempArr);
            tempArr.clear();
        }
        TwoDataFrames ret;
        ret.accepted = presentData;
        ret.rejected = absentData;
        return ret;
    }
    static void ConstructTree(TreeNode *node)
    {
        vector<int> targetsBefore = (node->trainData)[0];
        float giniBefore = TreeNode::GetGini(targetsBefore);

        if (node->bestSplit.resEntropy < giniBefore)
        {
            TwoDataFrames children = DecisionTree::splitData(node->trainData, node->bestSplit.Feature, node->bestSplit.Category);

            if (children.accepted[0].size() > 0)
            {
                TreeNode *rightChild = new TreeNode(children.accepted);
                node->rightChild = rightChild;
                DecisionTree::ConstructTree(node->rightChild);
            }
            if (children.rejected[0].size() > 0)
            {
                TreeNode *leftChild = new TreeNode(children.rejected);
                node->leftChild = leftChild;
                DecisionTree::ConstructTree(node->leftChild);
            }
        }
    }
    vector<int> Predict(DataFrame &targets)
    {
    }
    void DeleteChild(TreeNode *node)
    {
        if (node->rightChild != NULL)
        {
            DecisionTree::DeleteChild(node->rightChild);
        }
        if (node->leftChild != NULL)
        {
            DecisionTree::DeleteChild(node->leftChild);
        }
        delete node;
    }
    static int recursivePredict(TreeNode *node, vector<int> targets)
    {
        int obsCat = targets[node->bestSplit.Feature];
        int predict = -1;
        if (node->leftChild == NULL && (node->rightChild == NULL))
        {
            // THIS IS A LEAF NODE :: THE OUTCOME
            predict = (node->trainData)[0][1];
        }
        else if (obsCat == node->bestSplit.Category)
        {
            predict = DecisionTree::recursivePredict(node->rightChild, targets);
        }
        else
        {
            predict = DecisionTree::recursivePredict(node->leftChild, targets);
        }
        return predict;
    }
};

int main(int argc, char const *argv[])
{
    DecisionTree DT("DS-data.csv");
    vector<int> temp(1, 0);
    DataFrame test;
    test.push_back(temp);
    cout << DT.recursivePredict(DT.root, temp);
    // DT.traverseTree(DT.root);

    // for (auto n : DT.Data)
    // {
    //     for (auto num : n)
    //     {
    //         cout << num << ", ";
    //     }
    //     cout << endl;
    // }

    // DataFrame dt = DT.root->GetSplitTargets(DT.Data, 3, 1);
    // DT.root->GetBestSplit(DT.Data);
    // PrintData(dt);
    // vector<pair<int, int>> v = DT.CountResults(3); // -1 for overall and pass col index (0-4 from DATA(integers)) to get entropy of each attribute's attribute
    // for (auto n : v)
    // {
    //     cout << DT.EntropyOfCol(n) << endl;
    //     cout << n.first << ", " << n.second << endl;
    // }
    // cout << endl;
    // cout << DT.ColGain(DT.Data, 3) << endl;
    // for (int i = 0; i <= 4; i++)
    // {
    //     cout << DT.ColGain(DT.Data, i) << endl;
    // }
    // cout << DT.GetInfoGain(DT.Data) << endl;
    // PrintData(DT.Data);
    // DT.Split_Data(DT.Data, 0, 0);

    // Started 11/2/22
    // DT.Bit_Mask(DT.Data);
    // PrintData<int>(DT.Data);
    // pair<string, int> p = DT.getMajorityLabel(DT.DataInString);
    // cout << p.first << ", " << p.second << endl;

    return 0;
}
