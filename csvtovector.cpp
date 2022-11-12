#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main()
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
                record.push_back(row);
            }
        }
        for (int i = 0; i < record.size(); i++)
        {
            for (int j = 0; j < record[i].size(); j++)
            {
                cout << record[i][j] << " ";
            }
            cout << endl;
        }
    }
    else
    {
        cout << "Could not Open file";
    }
}