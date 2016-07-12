#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(20);
    parameters.setName("parameters");
    parameters.add(paramBrightness.set("Brightness",0.4f,0,1.0f));
    parameters.add(paramColour.set("Colour",ofColor(255,0,255)));
    parameters.add(paramPlayButton.set("Playing (spacebar)",true));
    parameters.add(paramEditButton.set("Edit Mode (e)",false));
    parameters.add(paramShowImageButton.set("Show Background (i)",true));
    setupGui();

    sync.setup(parameters,6667,"localhost",6666);
}

//--------------------------------------------------------------
void ofApp::setupGui()
{
    /* GUI */
    ofxDatGuiLog::quiet();
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );

    folder = gui->addFolder("Master Controls", ofColor::green);
    //gui_colour = folder->addColorPicker("Colour", ofColor(255,0,255));
    //folder->onColorPickerEvent(this, &ofApp::onColorPickerEvent);

    ofParameterGroup& p = parameters;

    for(int i = 0; i < p.size();i++) {
        if(p.getType(i) == "11ofParameterIfE") {
            folder->addSlider(p.getFloat(i));
        }
        else if(p.getType(i) == "11ofParameterIiE") {
            folder->addSlider(p.getInt(i));
        }
        else if(p.getType(i) == "11ofParameterIbE") {
            folder->addToggle(p.getBool(i));
        }
    }

    folder->expand();

//    gui->addHeader("LIGHT SETTINGS");
//    gui->addFooter();
//    gui_editLabel = gui->addLabel("");

//    gui_playButton = gui->addToggle("PLAYING",true);
//    gui_editButton = gui->addToggle("Edit Mode",false);
//    gui_showImageButton = gui->addToggle("Show Background Animation (i)",true);
//    gui_triggerBeginButton = gui->addButton("Trigger Animation Start (b)");
//    gui_nextAnimationButton = gui->addButton("Trigger Next Animation (n)");
    //gui->onButtonEvent(this, &ofApp::onButtonEvent);

    //gui->addBreak();

}

//--------------------------------------------------------------
//void ofApp::onColorPickerEvent(ofxDatGuiColorPickerEvent e)
//{
//    data.colour = e.color;
//}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{

//    else if (e.target == gui_showImageButton) {

//        if(e.enabled) {
//            data.bShowBgImage = true;
//        }
//        else {
//            data.bShowBgImage = false;
//        }
//    } else if (e.target == gui_editButton) {

//        if(e.enabled) {
//            bEditing = true;
//        }
//        else {
//            bEditing = false;
//        }
//    }
//    else if (e.target == gui_triggerBeginButton) {

//        if(e.enabled) {
//            animations.begin();
//        }
//    }

}

//--------------------------------------------------------------
void ofApp::update(){
    folder->update();
    sync.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    folder->setPosition(0, 0);
    folder->draw();
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
