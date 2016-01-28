#include "ofxTSNE.h"


vector<vector<float> > ofxTSNE::run(vector<vector<float> > & data, int dims, double perplexity, double theta, bool normalize) {
    int N, D;
    double *X, *Y;
    
    N = data.size();
    D = data[0].size();
    
    if (N - 1 < 3 * perplexity) {
        ofLog(OF_LOG_WARNING, "Perplexity too large for number of data points, setting to max");
        perplexity = (float) (N-1) / 3.0 - 1.0;
    }
    
    X = (double*) malloc(D * N * sizeof(double));
    Y = (double*) malloc(dims * N * sizeof(double));
    
    int idx = 0;
    for (int i=0; i<N; i++) {
        for (int j=0; j<D; j++) {
            X[idx] = data[i][j];
            idx++;
        }
    }

    // t-SNE
    tsne.run(X, N, D, Y, dims, perplexity, theta);
    
    // keep track of min for normalization
    vector<float> min_, max_;
    min_.resize(dims);
    max_.resize(dims);
    for (int i=0; i<dims; i++) {
        min_[i] = numeric_limits<float>::max();
        max_[i] = numeric_limits<float>::min();
    }
    
    // unpack Y into tsnePoints
    tsnePoints.clear();
    int idxY = 0;
    for (int i=0; i<N; i++) {
        vector<float> tsnePoint;
        tsnePoint.resize(dims);
        for (int j=0; j<dims; j++) {
            tsnePoint[j] = Y[idxY];
            if (normalize) {
                if (tsnePoint[j] < min_[j])  min_[j] = tsnePoint[j];
                if (tsnePoint[j] > max_[j])  max_[j] = tsnePoint[j];
            }
            idxY++;
        }
        tsnePoints.push_back(tsnePoint);
    }

    // normalize if requested
    if (normalize) {
        for (int i=0; i<tsnePoints.size(); i++) {
            for (int j=0; j<dims; j++) {
                tsnePoints[i][j] = ofMap(tsnePoints[i][j], min_[j], max_[j], 0, 1);
            }
        }
    }
    
    delete(X);
    delete(Y);

    return tsnePoints;
}
