//
// Created by davidzhu94 on 3/5/2017.
//

#ifndef CS170_FEATURESELECTION_INSTANCE_H
#define CS170_FEATURESELECTION_INSTANCE_H

#include <vector>

using namespace std;
class Instance {
public:
    int classLabel;
    vector<double> featureList;

    void printFeatures();
};


#endif //CS170_FEATURESELECTION_INSTANCE_H
