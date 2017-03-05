//
// Created by davidzhu94 on 3/5/2017.
//

#include "Instance.h"
#include <iostream>

using namespace std;

void Instance::printFeatures()
{
    for(int i = 0; i < featureList.size(); i++)
    {
        cout << featureList[i] << endl;
    }
}