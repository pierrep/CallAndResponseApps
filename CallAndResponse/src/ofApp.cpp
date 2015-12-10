#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofDisableArbTex(); // we need GL_TEXTURE_2D for our models coords.
    ofSetVerticalSync(false);
    ofSetFrameRate(120);
    loadTreeData(trees);

    //loader.load(trees);

    //cam.setDistance(10);
    cam.setup();
    cam.speed = 1.0f;
    //cam.loadCameraPosition();

    artnet.setup("192.168.0.2"); //make sure the firewall is deactivated at this point

    curTime = ofGetElapsedTimeMillis();
    prevTime - curTime;
    testPattern = 3;

    clearTrees();

    /* GUI */
    parameters.setName("LIGHT SETTINGS");
    parameters.add(brightness.set("brightness",0.5f,0.0f,1.0f));
    parameters.add(colour.set("colour",ofColor(127),ofColor(0,0),ofColor(255)));
    gui.setup(parameters);
}

//--------------------------------------------------------------
void ofApp::exit(){
    //cam.saveCameraPosition();

    clearTrees();
}

//--------------------------------------------------------------
void ofApp::update(){
    static int lightIndex = 0;
    static int pixelIndex = 0;

    curTime = ofGetElapsedTimeMillis();
    if(curTime - prevTime > 300) {
        prevTime = curTime;
        trees[0].clear();

        if(testPattern == 1) {
            trees[0].lights[lightIndex].setColour(ofColor::purple);
            lightIndex++;
            if(lightIndex > 4) lightIndex = 0;
        }
        else if(testPattern == 2) {
            lightIndex = (int) (pixelIndex / NUM_PIXELS_PER_FIXTURE);
            int pIdx = pixelIndex - (lightIndex * NUM_PIXELS_PER_FIXTURE);
            trees[0].lights[lightIndex].pixels[pIdx].setColour(ofColor::chartreuse);
            pixelIndex++;
            if(pixelIndex > (5*NUM_PIXELS_PER_FIXTURE - 1)) pixelIndex = 0;
        } else if(testPattern == 3) {
            for(int i = 0;i < trees[0].lights.size();i++)
            {
                trees[0].lights[i].setColour(colour);
                trees[0].lights[i].setBrightness(brightness);
            }
        }

    }

    for(int i = 0;i < trees.size();i++)
    {
        trees[i].update();
        int universe = trees[i].getId();
        artnet.sendDmx("192.168.0.11", 0, universe, trees[i].getBuffer(), 512);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();

    for(unsigned int i = 0; i < trees.size(); i++) {
        trees[i].draw();
    }

//    for(unsigned i = 0; i < lights.size(); i++) {
//        lights[i].draw();
//    }

    cam.end();

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

//--------------------------------------------------------------
void ofApp::clearTrees()
{
    for(int i = 0;i < trees.size();i++)
    {
        trees[i].clear();
        artnet.sendDmx("192.168.0.11", 0, trees[i].getId(), trees[i].getBuffer(), 512);
    }
}

//--------------------------------------------------------------
void ofApp::loadTreeData(vector<Tree>& trees)
{
    xml.load("TreeData.xml");
    xml.pushTag("Trees");

    int numTrees = xml.getNumTags("Tree");

    for(int t = 0; t < numTrees; t++)
    {
        xml.pushTag("Tree", t);
        int treeId = xml.getValue("TreeID",-1);
        string name = xml.getValue("TreeName","none");
        Tree tree;
        tree.setId(treeId);
        tree.setName(name);

        int numLights = xml.getNumTags("Light");

        for(int i = 0; i < numLights; i++)
        {
            int id = xml.getValue("Light:ID", 0, i);
            int x = xml.getValue("Light:X", 0, i);
            int y = xml.getValue("Light:Y", 0, i);

            LedFixture led;
            led.setId(id);
            led.setupPixels();
           // lights.push_back(led);
            tree.lights.push_back(led);
        }

        trees.push_back(tree);
        xml.popTag();
    }
    xml.popTag();

}
