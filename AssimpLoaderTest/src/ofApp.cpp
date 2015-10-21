#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofDisableArbTex(); // we need GL_TEXTURE_2D for our models coords.

    model.loadModel("E2-skeleton.obj", false);
    //model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75 , 0);
    vector<string> names;
    names = model.getMeshNames();

    cam.setDistance(10);
}

//--------------------------------------------------------------
void ofApp::update(){
    model.update();
    //mesh = model.getMesh(0);
    //mesh = model.getMesh("Tree_Num1");
    mesh = model.getMesh("Light_LED1");
    //cout << model.getMesh(0).getNumIndices() << endl;
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    drawModel();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::drawModel()
{
    ofSetColor(0);

	ofEnableDepthTest();

    ofPushMatrix();
        //model.drawWireframe();
        mesh.drawWireframe();
        ofVec3f c = mesh.getCentroid();
        ofSetColor(0,0,255);
        //ofSphere(c.x,c.y,c.z,1);
        //mesh.getVertices();
//        for(int i = 0 ; i < mesh.getNumVertices();i++) {
//          ofVec3f v = mesh.getVertices().at(i);
//        }
    ofPopMatrix();


    ofDisableDepthTest();

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
