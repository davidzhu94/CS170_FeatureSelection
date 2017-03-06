#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include "Instance.h"
using namespace std;

void parseFile();
void parseLine(string line);
double nearestNeighbour();
void nearestNeighbourProcess();


vector<Instance> testData;
vector<int> indexOfExclusions;
vector<int> selectedFeatures = {1};

int main() {
    double result;
    Instance test;
    parseFile();
    cout << nearestNeighbour();
    return 0;
}

void parseFile()
{
    string readClass;
    ifstream inFile("cs_170_small80.txt");
    while(inFile)
    {
        getline(inFile, readClass);
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

bool isExcluded(int checkMe)
{
    for(int i = 0; i < indexOfExclusions.size(); i++)
        if(checkMe == indexOfExclusions[i])
            return true;
    return false;
}

double euclideanDistance(Instance first, Instance second)
{
    double totalDistance = 0;
    for(int i = 0; i < selectedFeatures.size(); i++)
    {
        cout << "iteration number " << i << "is " << selectedFeatures[i] << endl;
        totalDistance += sqrt(pow(first.featureList[selectedFeatures[i]] - second.featureList[selectedFeatures[i]], 2));
    }
    return totalDistance;
}

double nearestNeighbour()
{
    int indexOfNearest = 0;
    int nearestValue = INT_MAX;
    double currentDistance;
    double correctGuess = 0;
    double percentageCorrect = 0;
    for(int i = 0; i < testData.size(); i++)
    {
        if(!isExcluded(i))
        {
            for(int j = 0; j < testData.size(); j++)
            {
                if(!isExcluded(j))
                {
                    currentDistance = euclideanDistance(testData[i], testData[j]);
                    cout << currentDistance << endl << endl;
                    if(currentDistance < nearestValue)
                    {
                        indexOfNearest = j;
                        nearestValue = currentDistance;
                    }
                }
            }
            if(testData[i].classLabel == testData[indexOfNearest].classLabel)
                correctGuess++;
        }
    }
    percentageCorrect = (double)(correctGuess/pow((testData.size() - selectedFeatures.size()), 2));
    return percentageCorrect;
}
