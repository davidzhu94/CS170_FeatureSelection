#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include "Instance.h"
using namespace std;

void parseFile(string filename);
void parseLine(string line);
double nearestNeighbour();
void exhaustiveSearch();
void forwardSelection();
void backwardSelection();

vector<Instance> testData;
vector<int> indexOfExclusions;
vector<int> selectedFeatures = {};

int main() {
    string filename;
    int selector;
    cout << "Welcome to David Zhu's Feature Selection Algorithm!" << endl;
    cout << "Please enter the name of the file to test: " << endl;
    cin >> filename;
    parseFile(filename);
    cout << endl << "Please select the algorithm you want to run" << endl;
    cout << endl << "1) Exhaustive Search" << endl << "2) Forward Selection" << endl << "3) Backward Selection" << endl;
    cin >> selector;
    cout << endl << "begin search!" << endl << endl;
    switch(selector)
    {
        case 1:
            exhaustiveSearch();
            break;
        case 2:
            forwardSelection();
            break;
        case 3:
            backwardSelection();
            break;
        default:
            cout << "Invalid Input" << endl;
    }
    
    return 0;
}
//cs_170_small80 copy.txt
void parseFile(string filename)
{
    string readClass;
    ifstream inFile(filename);
    while(inFile)
    {
        getline(inFile, readClass);
        parseLine(readClass);
    }
    inFile.close();
    cout << endl << "The dataset has " << testData[0].featureList.size() << " features with " << testData.size() << " instances." << endl;
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
        if(selectedFeatures[i] != -1)
            totalDistance += pow(first.featureList[selectedFeatures[i]] - second.featureList[selectedFeatures[i]], 2);
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
                    if(currentDistance < nearestValue)
                    {
                        indexOfNearest = j;
                        nearestValue = currentDistance;
                    }
                }
            }
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

void exhaustiveSearch()
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
        cout << "The highest percentage is " << highestPercentage << "% with feature(s) {";
        for(int k = 0; k < selectedFeatures.size(); k++)
        {
            if(k == selectedFeatures.size()-1)
                cout << selectedFeatures[k]+1 << "}" << endl;
            else
                cout << selectedFeatures[k]+1 << ",";
        }
        if(highestPercentage > bestPercentage)
        {
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

void forwardSelection()
{
    bool maxima = false;
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
                cout << "          Percentage of " << holder << "% with features {";
                for(int k = 0; k < selectedFeatures.size(); k++)
                {
                    if(k == selectedFeatures.size()-1)
                        cout << selectedFeatures[k]+1 << "}" << endl;
                    else
                        cout << selectedFeatures[k]+1 << ",";
                }
                selectedFeatures.pop_back();
            }
        }
        selectedFeatures.push_back(highestPercentageIndex);
        cout << endl << "The highest percentage is " << highestPercentage << "% with feature(s) {";
        for(int k = 0; k < selectedFeatures.size(); k++)
        {
            if(k == selectedFeatures.size()-1)
                cout << selectedFeatures[k]+1 << "}" << endl << endl;
            else
                cout << selectedFeatures[k]+1 << ",";
        }
        if(highestPercentage > bestPercentage && maxima)
        {
            cout << "New higher accuracy! Continuing to search!" << endl;
            maxima = false;
        }
        if(highestPercentage > bestPercentage)
        {
            bestPercentage = highestPercentage;
            indexOfBest.push_back(highestPercentageIndex);
        }
        if(highestPercentage < bestPercentage && maxima)
        {
            cout << "Accuracy is still lower than best accuracy!" << endl;
            break;
        }
        if(highestPercentage < bestPercentage && !maxima)
        {
            cout << "Accuracy decreased! Continue checking in case of local maxima" << endl;
            maxima = true;
        }
        highestPercentage = 0;
    }
    cout << "Finished Search! The best percentage is: " << bestPercentage << "% with feature(s): {";
    for(int i = 0; i < indexOfBest.size(); i++)
    {
        if(i == indexOfBest.size()-1)
            cout << selectedFeatures[i]+1 << "}" << endl;
        else
            cout << selectedFeatures[i]+1 << ",";
    }

}

bool backwardCheckFeatures()
{
    for(int i = 0; i < selectedFeatures.size(); i++)
    {
        if(selectedFeatures[i] != -1)
            return true;
    }
    return false;
}

void backwardSelection()
{
    for(int i = 0; i < testData[0].featureList.size(); i++)
        selectedFeatures.push_back(i);
    bool maxima = false;
    int featureIndexHolder;
    double holder = 0;
    double highestPercentage = 0;
    int highestPercentageIndex = 0;
    vector<int> indexOfBest;
    double bestPercentage = 0;
    while(backwardCheckFeatures())
    {
        for(int i = 0; i < testData[0].featureList.size(); i++)
        {
            if(selectedFeatures[i] != -1)
            {
                featureIndexHolder = selectedFeatures[i];
                selectedFeatures[i] = -1;
                holder = nearestNeighbour();
                if(holder >= highestPercentage)
                {
                    highestPercentage = holder;
                    highestPercentageIndex = i;
                }
                cout << "          Percentage of " << holder << " with feature(s) {";
                for(int k = 0; k < selectedFeatures.size(); k++)
                {
                    if(selectedFeatures[k] != -1)
                    {
                        if(k == selectedFeatures.size()-1)
                            cout << selectedFeatures[k]+1 << "}";
                        else
                            cout << selectedFeatures[k]+1 << ",";
                    }
                }
                if(selectedFeatures[selectedFeatures.size()-1] == -1)
                    cout << "}";
                cout << endl;
                selectedFeatures[i] = featureIndexHolder;
            }
        }
        selectedFeatures[highestPercentageIndex] = -1;
        cout << endl << "The highest percentage is " << highestPercentage << "% with feature(s) {";
        for(int k = 0; k < selectedFeatures.size(); k++)
        {
            if(selectedFeatures[k] != -1)
            {
                if(k == selectedFeatures.size()-1)
                    cout << selectedFeatures[k]+1 << "}";
                else
                    cout << selectedFeatures[k]+1 << ",";
            }
        }
        if(selectedFeatures[selectedFeatures.size()-1] == -1)
            cout << "}";
        cout << endl << endl;
        if(highestPercentage > bestPercentage && maxima)
        {
            cout << "New higher accuracy! Continuing to search!" << endl;
            maxima = false;
        }
        if(highestPercentage > bestPercentage)
        {
            bestPercentage = highestPercentage;
            indexOfBest = selectedFeatures;;
        }
        if(highestPercentage < bestPercentage && maxima)
        {
            cout << "Accuracy is still lower than best accuracy!" << endl;
            break;
        }
        if(highestPercentage < bestPercentage && !maxima)
        {
            cout << "Accuracy decreased! Continue checking in case of local maxima" << endl;
            maxima = true;
        }
        
        highestPercentage = 0;
    }
    cout << "The highest percentage is: " << bestPercentage << "% with feature(s): {";
    for(int i = 0; i < indexOfBest.size(); i++)
    {
        if(indexOfBest[i] != -1)
        {
            if(i == indexOfBest.size()-1)
                cout << indexOfBest[i]+1 << "}" << endl;
            else
                cout << indexOfBest[i]+1 << ",";
        }
    }

}
