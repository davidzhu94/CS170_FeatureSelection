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
vector<int> selectedFeatures = {};

int main() {
    double result;
    Instance test;
    parseFile();
    nearestNeighbourProcess();
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

bool isFeatured(int checkMe)
{
    for(int i = 0; i < selectedFeatures.size(); i++)
        if(checkMe == selectedFeatures[i])
            return true;
    return false;
}

double euclideanDistance(Instance first, Instance second)
{
    double totalDistance = 0;
    for(int i = 0; i < selectedFeatures.size(); i++)
    {
       // cout << "iteration number " << i << "is " << selectedFeatures[i] << endl;
        totalDistance += sqrt(pow(first.featureList[selectedFeatures[i]] - second.featureList[selectedFeatures[i]], 2));
    }
    return totalDistance;
}

double nearestNeighbour()
{
    int indexOfNearest = 0;
    double nearestValue = INT_MAX;
    double currentDistance;
    double correctGuess = 0;
    double percentageCorrect = 0;
    for(int i = 0; i < testData.size(); i++)
    {
        if(!isExcluded(i))
        {
            indexOfExclusions.push_back(i);
            for(int j = 0; j < testData.size(); j++)
            {
                if(!isExcluded(j))
                {
                    currentDistance = euclideanDistance(testData[i], testData[j]);
                   // cout << currentDistance << endl << endl;
                    if(currentDistance < nearestValue)
                    {
                       // cout << "The current closest: " << nearestValue << " The new closest: " << currentDistance << endl;
                        indexOfNearest = j;
                        nearestValue = currentDistance;
                    }
                }
            }
           // cout << "test data label is " <<testData[i].classLabel << " and comparing with  " <<testData[indexOfNearest].classLabel << endl;
            if(testData[i].classLabel == testData[indexOfNearest].classLabel)
                correctGuess++;
            nearestValue = INT_MAX;
            indexOfNearest = 0;
            indexOfExclusions.pop_back();
        }
    }
    percentageCorrect = (double)(correctGuess/(testData.size() - selectedFeatures.size()));
    return percentageCorrect * 100;
}

void nearestNeighbourProcess()
{
    double holder = 0;
    double highestPercentage = 0;
    int highestPercentageIndex = 0;
    vector<int> indexOfBest;
    double bestPercentage = 0;
    while(selectedFeatures.size() != testData[0].featureList.size())
    {
        for(int i = 0; i < testData[0].featureList.size(); i++)
        {
            if(!isFeatured(i))
            {
                selectedFeatures.push_back(i);
                holder = nearestNeighbour();
                if(holder > highestPercentage)
                {
                    highestPercentage = holder;
                    highestPercentageIndex = i;
                }
            selectedFeatures.pop_back();
            }
        }
        selectedFeatures.push_back(highestPercentageIndex);
        cout << "The highest percentage is " << highestPercentage << " with feature(s) {";
        for(int k = 0; k < selectedFeatures.size(); k++)
        {
            if(k == selectedFeatures.size()-1)
                cout << selectedFeatures[k]+1 << "}" << endl;
            else
                cout << selectedFeatures[k]+1 << ",";
        }
        if(highestPercentage > bestPercentage)
        {
            cout << "New best percentage == " << highestPercentage << endl;
            bestPercentage = highestPercentage;
            indexOfBest.push_back(highestPercentageIndex);
        }
                highestPercentage = 0;
    }
    cout << "The highest percentage is: " << bestPercentage << "% with feature(s): {";
    for(int i = 0; i < indexOfBest.size(); i++)
    {
        if(i == indexOfBest.size()-1)
            cout << selectedFeatures[i]+1 << "}" << endl;
        else
            cout << selectedFeatures[i]+1 << ",";
    }
}
