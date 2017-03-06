#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include "Instance.h"
using namespace std;

void parseFile();
void parseLine(string line);

vector<Instance> testData;

int main() {
    double result;
    Instance test;
    vector<int> items;
    parseFile();
    for(int i = 0; i < testData.size(); i++)
    {
        cout << "test data" << i << endl;
        testData[i].printFeatures();
    }
    cout << testData.size();
    return 0;
}

void parseFile()
{
    cout << "in function" << endl;
    string readClass;
    ifstream inFile("cs_170_small80.txt");
    while(inFile)
    {
        getline(inFile, readClass);
        cout << "getting line: " << endl<<endl << readClass <<endl<< endl;
        parseLine(readClass);
    }
    inFile.close();
}

void parseLine(string line)
{
    Instance inst;
    string holder;
    double feature;
    int classifier;
    u_int begin = 0;
    int i = 0;
    for(; i < line.length(); i++)
    {
        if(line[i] == ' ' && line[i+1] == ' ')
        {
            
            holder = line.substr(begin, i);
            if(holder != "")
            {
                classifier = ceil(stof(holder));
                inst.classLabel = classifier;
                i += 2;
                begin = i;
            break;
            }
        }
    }
    for(; i < line.length(); i++)
    {
        if(line[i] == ' ' && line[i+1] == ' ')
        {
            
            holder = line.substr(begin, i);
            feature = stof(holder);
            inst.featureList.push_back(feature);
            i += 2;
            begin = i;
        }
    }
    holder = line.substr(begin, line.length()-1);
    if(holder != "")
    {
        feature = stof(holder);
        inst.featureList.push_back(feature);
        testData.push_back(inst);
    }
}
