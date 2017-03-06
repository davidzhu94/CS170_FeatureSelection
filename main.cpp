#include <iostream>
#include <fstream>
#include <vector>
#include "Instance.h"
using namespace std;

void parseFile();
void parseLine(string line);

vector<Instance> testData;

int main() {
    cout << "hello" << endl;
    double result;
    Instance test;
    vector<int> items;
    parseLine("hello  world");
    string number = "1.23e+00";
    string number2 = "345";
    result = stof(number) + stoi(number2);
    cout << result << endl;
    for(int i = 0; i < testData.size(); i++)
    {
        testData[i].printFeatures();
    }
    return 0;
}

void parseFile()
{
    string readClass;
    ifstream inFile("cs_170_small80.txt");
    getline(inFile, readClass);
    cout << readClass << endl;
    while(inFile)
    {
        getline(inFile, readClass);
        cout << "hello" << endl;
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
    if(line[i] == ' ' && line[i+1] == ' ')
    {
        holder = line.substr(begin, i);
        classifier = stoi(holder);
        inst.classLabel = classifier;
        i += 2;
        begin = i;
    }
    for(; i < line.length(); i++)
    {
        if(line[i] == ' ' && line[i+1] == ' ')
        {
            holder = line.substr(begin, i);
            feature = stof(holder);
            cout << feature << endl;
            inst.featureList.push_back(feature);
            i += 2;
            begin = i;
        }
    }
    holder = line.substr(begin, line.length()-1);
    feature = stof(holder);
    inst.featureList.push_back(feature);
    testData.push_back(inst);
}
