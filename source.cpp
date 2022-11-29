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
        const vector<int> outputsBefore = data[0]; // Index 0
        this->trainData = data;
        this->bestSplit = GetBestSplit(data);
    }
    static vector<pair<int, int>> CountResults(MATRIX &Data, vector<int> &results, int index)
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
    static double EntropyOfCol(pair<int, int> p)
    {
        double total = double(p.first + p.second);
        double ret = -1 * (double(p.first / total) * log2(double(p.first / total))) - 1 * (double(p.second / total) * log2(double(p.second / total)));
        return (isnan(ret)) ? 0 : ret;
    }
    static double ColGain(MATRIX &data, int index)
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
    static pair<int, float> GetInfoGain(MATRIX &data)
    {
        if (data.size() == 0)
        {
            return {-1, 0.0f};
        }
        vector<float> cal;
        for (int i = 0; i <= 4; i++)
        {
            if (*find(selectedFeature.begin(), selectedFeature.end(), i))
            {
                cal.push_back(ColGain(data, i));
            }
        }
        int maxIndex = -1;
        for (int i = 0; i < 3; i++)
        {
            maxIndex = (cal[i] > cal[i + 1]) ? i : i + 1;
        }
        TreeNode::selectedFeature.push_back(maxIndex);
        float MaxRet = 0.f;
        cout << maxIndex << ", " << MaxRet << endl;
        for (auto n : cal)
        {
            MaxRet = max(MaxRet, n);
        }
        return {maxIndex, MaxRet};
    }
    static vector<int> GetColumn(MATRIX &dataT, int col)
    {
        vector<int> ret;
        for (int i = 0; i < dataT.size(); i++)
        {
            ret.push_back(dataT[i][col]);
        }
        return ret;
    }
    static float GetEntropy(MATRIX tempTrainData, vector<int> &outcomes)
    {
        if (outcomes.size() == 0)
        {
            return 0.0; // so that it doesn't divide by zero
        }
        return EntropyOfCol(CountResults(tempTrainData, outcomes, -1)[0]);
    }

    static MATRIX GetSplitTargets(MATRIX &dataT, int feature, int category)
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
            trueOutcomes.push_back(allOutcomes[i]);
        }
        for (auto i : falseSplit)
        {
            falseOutComes.push_back(allOutcomes[i]);
        }
        MATRIX ret;
        ret.push_back(trueOutcomes);
        ret.push_back(falseOutComes);
        return ret;
    }
    static bestSplitValues GetBestSplit(MATRIX &dataT)
    {
        // cout << " jsdf" << endl;
        // vector<int> outputBef = dataT[0];
        float Entropy = ColGain(dataT, 0);
        int Features = dataT[0].size() - 1;
        bestSplitValues bestChoice;
        bestChoice.Category = bestChoice.Feature = bestChoice.resEntropy = 0;
        int count{0};
        int max_count = INT_MIN;
        for (int f = 1; f < Features; f++)
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
            for (int c = 0; c < count; c++)
            {
                MATRIX split = GetSplitTargets(dataT, f, c);
                float trueEntropy = ColGain(split, 0);
                float weightedTrueEntropy = (float)trueEntropy * split[0].size() / dataT.size(); /// MASLAAAAA
                float falseEntropy = ColGain(split, 1);
                float weightedFalseEntropy = falseEntropy * split[1].size() / dataT.size();
                float sum = weightedTrueEntropy + weightedFalseEntropy;
                if (sum < bestChoice.resEntropy)
                {
                    bestChoice.resEntropy = sum;
                    bestChoice.Feature = f;
                    bestChoice.Category = c;
                }
            }
        }
        return bestChoice;
    }
};
vector<int> TreeNode::selectedFeature = {0};

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
};

int main(int argc, char const *argv[])
{
    DecisionTree DT("DS-data.csv");
    bestSplitValues b = DT.root->bestSplit;
    cout << b.resEntropy << ", " << b.Feature << ", " << b.Category << endl;

    return 0;
}
