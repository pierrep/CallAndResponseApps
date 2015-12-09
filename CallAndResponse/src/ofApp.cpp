#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofDisableArbTex(); // we need GL_TEXTURE_2D for our models coords.

    loadTreeData(trees);

    //loader.load(trees);

    //cam.setDistance(10);
    cam.setup();
    cam.speed = 1.0f;
    //cam.loadCameraPosition();

    artnet.setup("192.168.0.2"); //make sure the firewall is deactivated at this point
}

//--------------------------------------------------------------
void ofApp::exit(){
    //cam.saveCameraPosition();
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i = 0;i < trees.size();i++)
    {
        trees[i].update();
        artnet.sendDmx("192.168.0.11", 0, 0, trees[i].getBuffer(), 512);
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
void ofApp::loadTreeData(vector<Tree>& trees)
{
    xml.load("TreeData.xml");
    xml.pushTag("Trees");

    int numTrees = xml.getNumTags("Tree");

    for(int t = 0; t < numTrees; t++)
    {
        xml.pushTag("Tree", t);
        int treeId = xml.getValue("TreeID",0);
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
