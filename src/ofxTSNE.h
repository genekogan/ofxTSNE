#pragma once

#include "ofMain.h"
#include "tsne.h"

class ofxTSNE
{
public:
    vector<vector<double> > run(vector<vector<float> > & data, int dims=2, double perplexity=30, double theta=0.5, bool normalize=true, bool runManually=false);
    vector<vector<double> > iterate();
private:
    void finish();
    
    TSNE tsne;
    vector<vector<double> > tsnePoints;
    
    vector<vector<float> > data;
    int dims;
    double perplexity;
    double theta;
    bool normalize;
    bool runManually;
    
    int N, D;
    double *X, *Y;

    int iter, max_iter;
};
