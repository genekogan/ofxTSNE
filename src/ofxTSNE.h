#pragma once

#include "ofMain.h"
#include "tsne.h"

class ofxTSNE
{
public:
    vector<vector<float> > run(vector<vector<float> > & data, int dims=2, double perplexity=30, double theta=0.5, bool normalize=true);
private:
    TSNE tsne;
    vector<vector<float> > tsnePoints;
};
