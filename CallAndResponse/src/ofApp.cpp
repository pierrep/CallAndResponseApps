#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofDisableArbTex(); // we need GL_TEXTURE_2D for our models coords.
    ofSetVerticalSync(false);
    ofSetFrameRate(30);
    loadTreeData(trees);

    //loader.load(trees);

    //cam.setDistance(10);
    cam.setup();
    cam.speed = 1.0f;
    //cam.loadCameraPosition();

    artnet.setup("192.168.0.2"); //make sure the firewall is deactivated at this point

    curTime = ofGetElapsedTimeMillis();
    prevTime = curTime;
    testPattern = 3;
    curTimeTree = ofGetElapsedTimeMillis();
    prevTimeTree = curTimeTree;
    lightIndex = 0;
    pixelIndex = 0;

    clearTrees();
    currentTree = 0;
    wait_time = 4000;

    /* GUI */
    parameters.setName("LIGHT SETTINGS");
    parameters.add(brightness.set("brightness",0.4f,0.0f,1.0f));
    parameters.add(colour.set("colour",ofColor(255,0,255),ofColor(0),ofColor(255)));
    gui.setup(parameters);
}

//--------------------------------------------------------------
void ofApp::exit(){
    //cam.saveCameraPosition();

    clearTrees();
}

//--------------------------------------------------------------
void ofApp::update(){
    curTimeTree = ofGetElapsedTimeMillis();
    if(curTimeTree - prevTimeTree > wait_time)
    {
            if(currentTree >= 0) {
                currentTree = -1;
                wait_time = 6000;
            }
            else if(currentTree == -1 ) {
                currentTree = (int) ofRandom(0,8);
                wait_time = 4000;
            }
            prevTimeTree = curTimeTree;
            clearTrees();
    }

    if(currentTree < 0) return;


    curTime = ofGetElapsedTimeMillis();
    if(curTime - prevTime > 100) {
        prevTime = curTime;

        if(testPattern == 1) {
            trees[currentTree]->clear();
            trees[currentTree]->lights[lightIndex]->setColour(ofColor::purple);
            trees[currentTree]->lights[lightIndex]->setBrightness(1.0f);
            lightIndex++;
            if(lightIndex > 4) lightIndex = 0;
        }
        else if(testPattern == 2) {
            trees[currentTree]->clear();
            lightIndex = (int) (pixelIndex / NUM_PIXELS_PER_FIXTURE);
            int pIdx = pixelIndex - (lightIndex * NUM_PIXELS_PER_FIXTURE);
            trees[currentTree]->lights[lightIndex]->pixels[pIdx]->setColour(ofColor::chartreuse);
            trees[currentTree]->lights[lightIndex]->pixels[pIdx]->setBrightness(1.0f);
            pixelIndex++;
            if(pixelIndex > (5*NUM_PIXELS_PER_FIXTURE - 1)) pixelIndex = 0;
        } else if(testPattern == 3) {
            for(int i = 0;i < trees[currentTree]->lights.size();i++)
            {                
                trees[currentTree]->lights[i]->setColour(colour);
                trees[currentTree]->lights[i]->setBrightness(brightness);
                for(int j = 0; j < trees[currentTree]->lights[i]->pixels.size();j++) {
                    //float b = ofRandomuf();
                    //trees[currentTree]->lights[i]->pixels[j]->setBrightness(b);
                }
            }
        }
        else if(testPattern == 4) {
            for(int i = 0;i < trees[currentTree]->lights.size();i++)
            {
                trees[currentTree]->lights[i]->setColour(colour);
                //trees[currentTree]->lights[i]->setBrightness(brightness);
//                for(int j = 0; j < trees[currentTree]->lights[i]->pixels.size();j++) {
//                    float b = ofRandomuf();
//                    trees[currentTree]->lights[i]->pixels[j]->setBrightness(b);
//                }
            }
        }

    }

    for(int i = 0;i < trees.size();i++)
    {
        trees[i]->update();
        int universe = trees[i]->getId();
        artnet.sendDmx("192.168.0.11", 0, universe, trees[i]->getBuffer(), 512);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();

    for(unsigned int i = 0; i < trees.size(); i++) {
       // trees[i].draw();
    }

//    for(unsigned i = 0; i < lights.size(); i++) {
//        lights[i].draw();
//    }

    cam.end();

    gui.draw();

    ofSetupScreen();
    ofSetColor(0);
    if(currentTree >= 0)
        ofDrawBitmapString("Brightness: "+ofToString((int) trees[currentTree]->lights[0]->pixels[0]->getDMXValue(0)),20,ofGetHeight() - 40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key == '1') testPattern = 1;
    else if(key == '2') testPattern = 2;
    else if(key == '3') testPattern = 3;
    else if(key == '4') {testPattern = 4;

        for(int i = 0;i < trees[currentTree]->lights.size();i++)
        {
             trees[currentTree]->lights[i]->fadeOn();
        }
    }
    lightIndex = 0;
    pixelIndex = 0;
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

//--------------------------------------------------------------
void ofApp::clearTrees()
{
    for(int i = 0;i < trees.size();i++)
    {
        trees[i]->clear();
        artnet.sendDmx("192.168.0.11", 0, trees[i]->getId(), trees[i]->getBuffer(), 512);
    }
}

//--------------------------------------------------------------
void ofApp::loadTreeData(vector<Tree *>& trees)
{
    xml.load("TreeData.xml");
    xml.pushTag("Trees");

    int numTrees = xml.getNumTags("Tree");

    for(int t = 0; t < numTrees; t++)
    {
        xml.pushTag("Tree", t);
        int treeId = xml.getValue("TreeID",-1);
        string name = xml.getValue("TreeName","none");
        Tree* tree = new Tree();
        tree->setId(treeId);
        tree->setName(name);

        int numLights = xml.getNumTags("Light");

        for(int i = 0; i < numLights; i++)
        {
            int id = xml.getValue("Light:ID", 0, i);
            int x = xml.getValue("Light:X", 0, i);
            int y = xml.getValue("Light:Y", 0, i);

            LedFixture* led = new LedFixture();
            led->setId(id);
            led->setupPixels();
           // lights.push_back(led);
            tree->lights.push_back(led);
        }

        trees.push_back(tree);
        xml.popTag();
    }
    xml.popTag();

}
