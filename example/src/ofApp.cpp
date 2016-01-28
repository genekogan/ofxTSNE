#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // first let's construct our toy dataset.
    // we will create N samples of dimension D, which will be distributed
    // into a number of classes, where a point belonging to a particular
    // class will be located close to the center point for that class.
    // Note: TSNE doesn't operate on classes/labels and you don't need to
    // use them. we are creating the dataset with color-coded classes
    // so we can see TSNE's ability to retain clusters of points when
    // transforming them from high-dimensional to low-dimensional space, so
    // in this example, the classes are just for us to see this clearer.
    
    // pick initial parameters
    int N = 2000;               // number of points in our dataset
    int D = 100;                // number of dimensions in our data
    int numClasses = 10;        // how many classes to create
    
    
    // first let's make our classes
    
    vector<ofColor> classColors = vector<ofColor>{ofColor::red, ofColor::green,
        ofColor::blue, ofColor::cyan, ofColor::magenta, ofColor::black,
        ofColor::yellow, ofColor::violet, ofColor::pink, ofColor::gray};
    vector<vector<float> > classCenters;
    classCenters.resize(numClasses);
    
    for (int i = 0; i < numClasses; i++) {
        // pick a random center point for this class
        vector<float> classCenter;
        classCenter.resize(D);
        for (int j=0; j<D; j++) {
            classCenter[j] = ofRandom(1);
        }
        classCenters[i] = classCenter;
    }
    
    
    // now that we have defined our classes, let's make a fake dataset with N
    // points randomly distributed into our classes. we will store them as
    // a vector of TestPoints which contain the point and class assignment.
    // we will use ofxTSNE to determine the 2-dimensional t-SNE point for each
    // TestPoint.point
    
    testPoints.clear();
    
    for (int i = 0; i < N; i++) {
        // choose a random class
        int class_ = ofRandom(numClasses);
        vector<float> point;
        point.resize(D);
        
        // the TestPoint will be located with some (fairly large) random
        // deviation from the center point of its class
        for (int j=0; j<D; j++) {
            point[j] = classCenters[class_][j] + ofRandom(-1.5, 1.5);
        }
        
        // save the point and class information in a TestPoint
        TestPoint testPoint;
        testPoint.class_ = class_;
        testPoint.color = classColors[class_];
        testPoint.point = point;
        
        testPoints.push_back(testPoint);
    }
    
    
    // now lets run our points through ofxTSNE.  ofxTSNE takes the data
    // as a vector<vector<float> > where the inner vector<float> corresponds
    // to a single data point. So let's unpack our testPoints into this.
    
    vector<vector<float> > data;
    for (int i = 0; i < N; i++) {
        data.push_back(testPoints[i].point);
    }
    
    // ofxTSNE takes four parameters:
    //
    // dims = number of dimensions to embed our points into. we will
    //   use 2 points to visualize along (x, y), although t-SNE is commonly
    //   used for 3d as well. since t-SNE is best known for visualization,
    //   it's most commonly run with 2 or 3 dims, but more can be used.
    // perplexity = a measure of the dataset's Shannon entropy, this can be
    //   loosely interpreted as how uncertain the data is / how difficult it is
    //   to be modeled by a probability distribution. generally speaking, larger
    //   datasets need a higher perplexity, but if your points end up looking
    //   like a poorly-arranged uniformly-distributed ball, your perplexity is
    //   too high. this value is usually set between 5 and 50 with 30 being
    //   a good default. t-SNE is fairly insensitive to this parameter so
    //   in most cases the default should work fine.
    // theta / angle = this parameter controls the accuracy/speed tradeoff
    //   of the Barnes-Hut simulation used to solve the t-SNE embedding. low
    //   theta is more accurate but slower, and high theta is faster but
    //   maybe less optimal solution. it should be between 0 and 1. in practice
    //   you can usually get away with higher theta (say 0.5) without sacrificing
    //   noticeable accuracy.
    // normalize = this will automatically remap all tsne points to range {0, 1}
    //   if false, you'll get the original points.
    
    
    int dims = 2;
    float perplexity = 30;
    float theta = 0.5;
    bool normalize = true;
    
    // finally let's run ofxTSNE! this may take a while depending on your
    // data, and it will return a set of embedded points, structured as
    // a vector<vector<float> > where the inner vector contains (dims) elements.
    // We will unpack these points and assign them back to our testPoints dataset.
    
    vector<vector<float> > tsnePoints = tsne.run(data, dims, perplexity, theta, normalize);

    // unpack the embedded points back into our testPoints
    for (int i=0; i<N; i++) {
        testPoints[i].tsnePoint = ofPoint(tsnePoints[i][0], tsnePoints[i][1]);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    for (int i=0; i<testPoints.size(); i++) {
        float x = ofGetWidth() * testPoints[i].tsnePoint.x;
        float y = ofGetHeight() * testPoints[i].tsnePoint.y;
        ofSetColor(testPoints[i].color, 150);
        ofDrawEllipse(x, y, 8, 8);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
