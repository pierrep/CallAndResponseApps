#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    ofSetVerticalSync(false);
    ofSetFrameRate(30);

    data.load();
    editor.setup(&data);
    guiMap.setup(&data);
    bArtNetActive = artnet.setup("192.168.0.2"); //make sure the firewall is deactivated at this point

    curTime = ofGetElapsedTimeMillis();
    prevTime = curTime;
    testPattern = 1;
    curTimeTree = ofGetElapsedTimeMillis();
    prevTimeTree = curTimeTree;
    lightIndex = 0;
    pixelIndex = 0;

    clearTrees();    
    wait_time = 4000;

    /* GUI */
//    parameters.setName("LIGHT SETTINGS");
//    parameters.add(brightness.set("brightness",0.4f,0.0f,1.0f));
//    parameters.add(colour.set("colour",ofColor(255,0,255),ofColor(0),ofColor(255)));
//    gui.setup(parameters);

    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );

    ofxDatGuiFolder* folder = gui->addFolder("Master Controls", ofColor::green);
    brightness = folder->addSlider("Brightness", 0, 1, 0.4f);
    colour = folder->addColorPicker("Colour", ofColor(255,0,255));
    folder->expand();

    gui->addHeader("LIGHT SETTINGS");
    gui->addFooter();
    gui->setPosition(ofGetWidth() - gui->getWidth(), 0);

    playButton = gui->addToggle("PLAYING");
    gui->onButtonEvent(this, &ofApp::onButtonEvent);


}

//--------------------------------------------------------------
void ofApp::exit(){

    data.save();
    clearTrees();
}

//--------------------------------------------------------------
void ofApp::update(){
    curTimeTree = ofGetElapsedTimeMillis();
    if((curTimeTree - prevTimeTree > wait_time) && (data.isPlaying))
    {
            if(data.state == data.LIGHTS_ON) {
                data.state = data.LIGHTS_OFF;
                wait_time = 6000;
            }
            else if(data.state == data.LIGHTS_OFF ) {
                data.currentTree = (int) ofRandom(0,8);
                //data.currentTree = 0;
                data.state = data.LIGHTS_ON;
                wait_time = 4000;
            }
            prevTimeTree = curTimeTree;
            clearTrees();
    }

    if(data.state == data.LIGHTS_OFF) return;


    curTime = ofGetElapsedTimeMillis();
    if(curTime - prevTime > 100) {
        prevTime = curTime;

        if(testPattern == 1) {
            data.trees[data.currentTree]->clear();
            data.trees[data.currentTree]->lights[lightIndex]->setColour(ofColor::purple);
            data.trees[data.currentTree]->lights[lightIndex]->setBrightness(1.0f);
            lightIndex++;
            if(lightIndex > 4) lightIndex = 0;
        }
        else if(testPattern == 2) {
            data.trees[data.currentTree]->clear();
            lightIndex = (int) (pixelIndex / NUM_PIXELS_PER_FIXTURE);
            int pIdx = pixelIndex - (lightIndex * NUM_PIXELS_PER_FIXTURE);
            data.trees[data.currentTree]->lights[lightIndex]->pixels[pIdx]->setColour(ofColor::chartreuse);
            data.trees[data.currentTree]->lights[lightIndex]->pixels[pIdx]->setBrightness(1.0f);
            pixelIndex++;
            if(pixelIndex > (5*NUM_PIXELS_PER_FIXTURE - 1)) pixelIndex = 0;
        } else if(testPattern == 3) {
            for(int i = 0;i < data.trees[data.currentTree]->lights.size();i++)
            {                
                data.trees[data.currentTree]->lights[i]->setColour(colour->getColor());
                data.trees[data.currentTree]->lights[i]->setBrightness(brightness->getValue());
                for(int j = 0; j < data.trees[data.currentTree]->lights[i]->pixels.size();j++) {
                    //float b = ofRandomuf();
                    //data.trees[data.currentTree]->lights[i]->pixels[j]->setBrightness(b);
                }
            }
        }
        else if(testPattern == 4) {
            for(int i = 0;i < data.trees[data.currentTree]->lights.size();i++)
            {
                data.trees[data.currentTree]->lights[i]->setColour(colour->getColor());
                //data.trees[data.currentTree]->lights[i]->setBrightness(brightness);
//                for(int j = 0; j < data.trees[data.currentTree]->lights[i]->pixels.size();j++) {
//                    float b = ofRandomuf();
//                    data.trees[data.currentTree]->lights[i]->pixels[j]->setBrightness(b);
//                }
            }
        }

    }


    for(int i = 0;i < data.trees.size();i++)
    {
        data.trees[i]->update();
        int universe = data.trees[i]->getId();
        if(bArtNetActive) artnet.sendDmx("192.168.0.11", 0, universe, data.trees[i]->getBuffer(), 512);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetWindowTitle("X = "+ofToString(mouseX)+" Y = "+ofToString(mouseY));

    guiMap.draw(0,0,400,900);
    editor.draw(400,0,1200,900);

    //gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if((key == 'f') || (key == 'F')) {
        ofToggleFullscreen();
    }

    if(key == '1') testPattern = 1;
    else if(key == '2') testPattern = 2;
    else if(key == '3') testPattern = 3;
    else if(key == '4') {testPattern = 4;

        for(int i = 0;i < data.trees[data.currentTree]->lights.size();i++)
        {
             data.trees[data.currentTree]->lights[i]->fadeOn();
        }
    }
    lightIndex = 0;
    pixelIndex = 0;
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    if (e.target == playButton){
        if(e.target->getLabel() == "PLAYING") {
            e.target->setLabel("PAUSED");
            data.isPlaying = false;
            editor.enableEditing();
        } else {
            e.target->setLabel("PLAYING");
            data.isPlaying = true;
            editor.disableEditing();
        }
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

//--------------------------------------------------------------
void ofApp::clearTrees()
{
    for(int i = 0;i < data.trees.size();i++)
    {
        data.trees[i]->clear();
        if(bArtNetActive) artnet.sendDmx("192.168.0.11", 0, data.trees[i]->getId(), data.trees[i]->getBuffer(), 512);
    }
}

