#include "ofApp.h"

const string allowed_ext[] = {"jpg", "png", "gif", "jpeg"};

void ofApp::scan_dir_imgs(ofDirectory dir){
    ofDirectory new_dir;
    int size = dir.listDir();
    for (int i = 0; i < size; i++){
        if (dir.getFile(i).isDirectory()){
            new_dir = ofDirectory(dir.getFile(i).getAbsolutePath());
            new_dir.listDir();
            new_dir.sort();
            scan_dir_imgs(new_dir);
        } else if (std::find(std::begin(allowed_ext),
                             std::end(allowed_ext),
                             dir.getFile(i).getExtension()) != std::end(allowed_ext)) {
            imageFiles.push_back(dir.getFile(i));
        }
    }
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    // SETUP
    // imageDir, imageSavePath = location of images, path to save the final grid image
    // nx, ny = size of the grid (make sure there are at least nx*ny images in imageDir!)
    // w, h = size of the image thumbnails
    // perplexity, theta (for t-SNE, see 'example' for explanation of these)
    string imageDir = "/Users/gene/Media/ImageSets/animals";
    string imageSavePath = "tsne_grid_animals.png";
    nx = 48;
    ny = 36;
    w = 100;
    h = 100;
    perplexity = 75;
    theta = 0.001;

    
    /////////////////////////////////////////////////////////////////////
    // CCV activations -> t-SNE embedding -> grid assignments
    
    // get images recursively from directory
    ofLog() << "Gathering images...";
    ofDirectory dir = ofDirectory(imageDir);
    scan_dir_imgs(dir);
    if (imageFiles.size() < nx * ny) {
        ofLog(OF_LOG_ERROR, "There are less images in the directory than the grid size requested (nx*ny="+ofToString((nx*ny))+"). Exiting to save you trouble...");
        ofExit(); // not enough images to fill the grid, so quitting
    }
    
    // load all the images
    for(int i=0; i<nx*ny; i++) {
        if (i % 20 == 0)    ofLog() << " - loading image "<<i<<" / "<<nx*ny<<" ("<<dir.size()<<" in dir)";
        images.push_back(ofImage());
        images.back().load(imageFiles[i]);
    }

    // resize images to w x h
    for (int i=0; i<images.size(); i++) {
        if (images[i].getWidth() > images[i].getHeight()) {
            images[i].crop((images[i].getWidth()-images[i].getHeight()) * 0.5, 0, images[i].getHeight(), images[i].getHeight());
        }
        else if (images[i].getHeight() > images[i].getWidth()) {
            images[i].crop(0, (images[i].getHeight()-images[i].getWidth()) * 0.5, images[i].getWidth(), images[i].getWidth());
        }
        images[i].resize(w, h);
    }
    
    // setup ofxCcv
    ccv.setup("image-net-2012.sqlite3");
    
    // encode all of the images with ofxCcv
    ofLog() << "Encoding images...";
    for (int i=0; i<images.size(); i++) {
        if (i % 20 == 0) ofLog() << " - encoding image "<<i<<" / "<<images.size();
        vector<float> encoding = ccv.encode(images[i], ccv.numLayers()-1);
        encodings.push_back(encoding);
    }
    
    // run t-SNE and load image points to imagePoints
    ofLog() << "Run t-SNE on images";
    tsneVecs = tsne.run(encodings, 2, perplexity, theta, true);
    
    // solve assignment grid
    vector<ofVec2f> tsnePoints; // convert vector<double> to ofVec2f
    for (auto t : tsneVecs) tsnePoints.push_back(ofVec2f(t[0], t[1]));
    vector<ofVec2f> gridPoints = makeGrid(nx, ny);
    solvedGrid = solver.match(tsnePoints, gridPoints, false);
    
    // save
    ofFbo fbo;
    fbo.allocate(nx * w, ny * h);
    fbo.begin();
    ofClear(0, 0);
    ofBackground(0);
    for (int i=0; i<solvedGrid.size(); i++) {
        float x = (fbo.getWidth() - w) * solvedGrid[i].x;
        float y = (fbo.getHeight() - h) * solvedGrid[i].y;
        images[i].draw(x, y, w, h);
    }
    fbo.end();
    ofImage img;
    fbo.readToPixels(img);
    img.save(imageSavePath);
    
    // setup gui
    gui.setup();
    gui.add(scale.set("scale", 1.0, 0.0, 1.0));
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    ofPushMatrix();
    ofTranslate(-ofGetMouseX() * (scale - 0.5), -ofGetMouseY() * (scale - 0.5));
    for (int i=0; i<solvedGrid.size(); i++) {
        float x = scale * (nx - 1) * w * solvedGrid[i].x;
        float y = scale * (ny - 1) * h * solvedGrid[i].y;
        images[i].draw(x, y, scale * images[i].getWidth(), scale * images[i].getHeight());
    }
    ofPopMatrix();
    
    gui.draw();
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
