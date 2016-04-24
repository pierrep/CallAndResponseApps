#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(50,50,50);
    ofSetVerticalSync(false);
    ofSetFrameRate(30);

    data.load();
    editor.setup(&data);
    guiMap.setup(&data);
    animations.setup(&data);
    bArtNetActive = artnet.setup("192.168.0.3"); //make sure the firewall is deactivated at this point
    if(!bArtNetActive) {
        memset( dmxData_, 0, DMX_DATA_LENGTH );
        dmxInterface_ = ofxGenericDmx::openFirstDevice();
        if ( dmxInterface_ == 0 ) {
            ofLog(OF_LOG_ERROR, "No Enttec Device Found" );
            bDmxUsbActive = false;
        }
        else {
            ofLog(OF_LOG_NOTICE,"isOpen: %i", dmxInterface_->isOpen() );
            bDmxUsbActive = true;
        }

    }
    bEditing = false;

    clearTrees();    

    setupGui();

    curTimeTree = ofGetElapsedTimeMillis();
    prevTimeTree = curTimeTree;
    wait_time = 4000;
    animations.load();
    animations.begin();
}

//--------------------------------------------------------------
void ofApp::exit(){

    data.save();
    animations.save();
    clearTrees();  

}

//--------------------------------------------------------------
void ofApp::update(){
    curTimeTree = ofGetElapsedTimeMillis();
    if((curTimeTree - prevTimeTree > wait_time) && (data.isPlaying))
    {
            if(data.state == data.LIGHTS_ON) {
                data.state = data.LIGHTS_OFF;
                wait_time = 1000;
            }
            else if(data.state == data.LIGHTS_OFF ) {
                data.currentTree = (int) ofRandom(0,8);
                //data->currentTree = 0;
                data.state = data.LIGHTS_ON;
                if(!editor.isEditing()) {
                    animations.begin();
                }
                wait_time = 10000;
            }
            prevTimeTree = curTimeTree;
            clearTrees();
    }

    if(data.state == data.LIGHTS_OFF) return;

    if(!editor.isEditing()) {
        animations.update();
    }

    data.colour = gui_colour->getColor();
    data.brightness = gui_brightness->getValue();

    for(int i = 0;i < data.trees.size();i++)
    {
        data.trees[i]->update();
        int universe = data.trees[i]->getId();
        updateTreeDMX(i);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetWindowTitle("X = "+ofToString(mouseX)+" Y = "+ofToString(mouseY) + " fps:"+ofToString(ofGetFrameRate()));

    guiMap.draw(0,0,400,900);
    animations.draw(400,0);
    if(editor.isEditing()) {

    }
    editor.draw(400,0,1200,900);
    animations.drawGui();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if((key == 'f') || (key == 'F')) {
        ofToggleFullscreen();
    }

    if(key == 'e') {
        if(gui_editLabel->getLabel() == "") {
            gui_editLabel->setLabel("EDITING");
            editor.enableEditing();
        } else {
            gui_editLabel->setLabel("");
            editor.disableEditing();
        }

    }
    if(key == ' ') {
        gui_playButton->toggle();
        if(gui_playButton->getLabel() == "PLAYING") {
            gui_playButton->setLabel("PAUSED");
            data.isPlaying = false;
        } else {
            gui_playButton->setLabel("PLAYING");
            data.isPlaying = true;
        }
    }

    if(key == 'i') {
        gui_showImageButton->toggle();
        if(gui_showImageButton->getEnabled()) {
            data.bShowBgImage = true;
        }
        else {
            data.bShowBgImage = false;
        }
    }

    if(key == '1') animations.setTestPattern(1);
    else if(key == '2') animations.setTestPattern(2);
    else if(key == '3') animations.setTestPattern(3);
    else if(key == '4')
    {
        animations.setTestPattern(4);

        for(int i = 0;i < data.trees[data.currentTree]->lights.size();i++)
        {
             data.trees[data.currentTree]->lights[i]->fadeOn();
        }
    }
    else if(key == '5') animations.setTestPattern(5);


    if(key == 'n') {
        animations.nextEffect();
    }

}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    if (e.target == gui_playButton){
        if(e.target->getLabel() == "PLAYING") {
            e.target->setLabel("PAUSED");
            data.isPlaying = false;
        } else if (e.target->getLabel() == "PAUSED") {
            e.target->setLabel("PLAYING");
            data.isPlaying = true;
        }
    } else if (e.target == gui_showImageButton) {

        if(e.enabled) {
            data.bShowBgImage = true;
        }
        else {
            data.bShowBgImage = false;
        }
    }
}

//--------------------------------------------------------------
void ofApp::onColorPickerEvent(ofxDatGuiColorPickerEvent e)
{
    data.colour = e.color;
}

//--------------------------------------------------------------
void ofApp::setupGui()
{
    /* GUI */
    ofxDatGuiLog::quiet();
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );

    ofxDatGuiFolder* folder = gui->addFolder("Master Controls", ofColor::green);
    gui_brightness = folder->addSlider("Brightness", 0, 1, 1.0f);
    gui_colour = folder->addColorPicker("Colour", ofColor(255,0,255));
    folder->onColorPickerEvent(this, &ofApp::onColorPickerEvent);

    folder->expand();

    gui->addHeader("LIGHT SETTINGS");
    gui->addFooter();
    gui->setPosition(ofGetWidth() - gui->getWidth(), 0);

    gui_editLabel = gui->addLabel("");
    gui_playButton = gui->addToggle("PLAYING",true);
    gui_showImageButton = gui->addToggle("SHOW BACKGROUND IMAGE (i)",true);
    gui->onButtonEvent(this, &ofApp::onButtonEvent);

    gui->addBreak();

}

//--------------------------------------------------------------
void ofApp::updateTreeDMX(int i)
{
    if(bArtNetActive) artnet.sendDmx("192.168.0.11", 0, data.trees[i]->getId(), data.trees[i]->getBuffer(), 512);
    else if(bDmxUsbActive) {
        if(i == 0) { //only send 1st tree
        dmxData_[0] = 0;
        memcpy(&dmxData_[1],data.trees[i]->getBuffer(),512);
        dmxInterface_->writeDmx( dmxData_, DMX_DATA_LENGTH );
        }
    }
}

//--------------------------------------------------------------
void ofApp::clearTrees()
{
    for(int i = 0;i < data.trees.size();i++)
    {
        data.trees[i]->clear();
        updateTreeDMX(i);
    }
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
    gui->setPosition(ofGetWidth() - gui->getWidth(), 0);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}


