#include "ofApp.h"

ofApp::ofApp() :
    gBloomTime(5000.0f),
    gTrailTime(2000.0f),
    gPauseTime(3000.0f)
{

}

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(50,50,50);
    ofSetVerticalSync(false);
    ofSetFrameRate(30);
    ofSetLogLevel(OF_LOG_SILENT);

    data.load();
    editor.setup(&data);
    guiMap.setup(&data);
    animations.setup(&data);
    bArtNetActive = artnet.setup("192.168.0.43"); //make sure the firewall is deactivated at this point
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


    ofxKeyframeAnimRegisterEvents(this);

    curTimeTree = ofGetElapsedTimeMillis();
    prevTimeTree = curTimeTree;
    wait_time = 4000;

    playhead = 0.0f;
    bloomCount = 0;
    animations.load();

    ofLogNotice() << "Start Bloom\t time: " << ofGetElapsedTimeMillis() << " current tree: " << data.currentTree << " target tree: " << data.targetTree;
    data.currentTree = data.nextTree;
    bloomTree();

    playhead = 0.0f;
    timeline.addKeyFrame(Action::tween(gBloomTime, &playhead, 1.0f,TWEEN_LIN,TWEEN_EASE_OUT));
    timeline.addKeyFrame(Action::event(this,"END_BLOOM"));
}

//--------------------------------------------------------------
void ofApp::exit(){

    data.save();
    animations.save();
    clearTrees();  

}

//--------------------------------------------------------------
void ofApp::bloomTree()
{

    if(data.currentTree == data.targetTree) {

        animations.setEffect(1);
        animations.enableEffect(4);         /* TODO: REFERENCE FX BY NAME NOT INDEX!! */

    } else {
        animations.setEffect(2);
    }

    if(!editor.isEditing()) {
        animations.begin();
    }

}

//--------------------------------------------------------------
int ofApp::calculateRandomTree()
{

   int tree = (int) ofRandom(0,8);
    while(abs(tree - data.currentTree) < 2) {
        tree = (int) ofRandom(0,8);
    }

//    if(data.currentTree == 7 && tree == 0) tree = 1;
//    if(data.currentTree == 0 && tree == 7) tree = 6;

    ofLogNotice() << "New target tree: " << tree << "(current tree: " << data.currentTree <<")";
    return tree;
}

//--------------------------------------------------------------
int ofApp::getNextTree()
{
    int tree = data.currentTree;

//    if(tree == 3) return 0;
//    else if(tree == 0) return 3;
//    else
        tree--;

    if(tree < 0 ) {
        tree = data.trees.size()-1;
    }
    else if(tree > data.trees.size()-1) {
        tree = 0;
    }

    return tree;
}

//--------------------------------------------------------------
void ofApp::onKeyframe(ofxPlaylistEventArgs& args)
{
    // this check is only necessary if you want to be absolutely sure that the onKeyFrame Event was sent by the same object as the receiver.
   // if (args.pSender != static_cast<void*>(this)) return;
   // ofLog(OF_LOG_VERBOSE) << "Keyframe Event received for (" << args.pSender << "): " << args.message << ": " << ofGetFrameNum();

    if(args.message == "END_BLOOM") {
        data.state = data.END_BLOOM;

    } else if(args.message == "END_TRAIL") {
        data.state = data.END_TRAIL;

    } else if(args.message == "START_BLOOM") {
        data.state = data.START_BLOOM;

    } else if(args.message == "START_TRAIL") {
        data.state = data.START_TRAIL;
    }
}

//--------------------------------------------------------------
void ofApp::processState()
{
    switch (data.state)
    {
        case data.START_BLOOM:
        {
            ofLogNotice() << " ";
            ofLogNotice() << "Start Bloom\t time: " << ofGetElapsedTimeMillis() << " current tree: " << data.currentTree << " target tree: " << data.targetTree;
            clearTrees();
            if(data.isPlaying) {
                data.state = data.LIGHTS_ON;
                bloomTree();
            }

            playhead = 0.0f;
            timeline.addKeyFrame(Action::tween(gBloomTime, &playhead, 1.0f,TWEEN_LIN,TWEEN_EASE_OUT));
            timeline.addKeyFrame(Action::event(this,"END_BLOOM"));
            break;
        }
        case data.END_BLOOM:
        {
            ofLogNotice() << "End Bloom  \t time: " << ofGetElapsedTimeMillis() << " current tree: " << data.currentTree << " target tree: " << data.targetTree;
            //clearTrees();
            if(data.isPlaying) {
                data.state = data.LIGHTS_OFF;
            }

            playhead = 0.0f;
            bloomCount++;
            if(bloomCount == 2) {
                ofLogNotice() << "End call & response...start a new one.";
                timeline.addKeyFrame(Action::pause(gPauseTime));
                data.targetTree = calculateRandomTree();
                data.currentTree = data.targetTree;
                data.nextTree = data.currentTree;
                timeline.addKeyFrame(Action::event(this,"START_BLOOM"));
                bloomCount = 0;
                return;
            }

            data.targetTree = calculateRandomTree();

            data.nextTree = getNextTree();
            timeline.addKeyFrame(Action::event(this,"START_TRAIL"));
            break;
        }
        case data.START_TRAIL:
        {
            ofLogNotice() << "Start Trail\t time: " << ofGetElapsedTimeMillis() << " current tree: " << data.currentTree << " target tree: " << data.targetTree;
            clearTrees();
            if(data.isPlaying) {
                data.state = data.LIGHTS_ON;
                data.currentTree = data.nextTree;
                bloomTree();
            }

            playhead = 0.0f;
            timeline.addKeyFrame(Action::tween(gTrailTime, &playhead, 1.0f,TWEEN_LIN,TWEEN_EASE_OUT));
            timeline.addKeyFrame(Action::event(this,"END_TRAIL"));
            break;
        }
        case data.END_TRAIL:
        {
            ofLogNotice() << "End Trail  \t time: " << ofGetElapsedTimeMillis() << " current tree: " << data.currentTree << " target tree: " << data.targetTree;
            //clearTrees();
            if(data.isPlaying) {
                data.state = data.LIGHTS_OFF;
            }

            playhead = 0.0f;

            data.nextTree = getNextTree();

            if(data.nextTree == data.targetTree) {
                timeline.addKeyFrame(Action::event(this,"START_BLOOM"));
                data.currentTree = data.nextTree;
            } else {
                timeline.addKeyFrame(Action::event(this,"START_TRAIL"));
            }
            break;
        }
        case data.LIGHTS_OFF:
        case data.LIGHTS_ON:
        default:
        {
            break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){

    timeline.update();

    processState();



    if(data.state == data.LIGHTS_OFF) return;

    if(!editor.isEditing()) {
        animations.update(playhead);
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

    if(key == '1') animations.setPattern(1);
    else if(key == '2') animations.setPattern(2);
    else if(key == '3') animations.setPattern(3);
    else if(key == '4')
    {
        animations.setPattern(4);

        for(int i = 0;i < data.trees[data.currentTree]->lights.size();i++)
        {
             data.trees[data.currentTree]->lights[i]->fadeOn();
        }
    }
    else if(key == '5') animations.setPattern(5);


    if(key == 'n') {
        animations.nextEffect();
    }
    if(key == 'b') {
        animations.begin();
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
    } else if (e.target == gui_editButton) {

        if(e.enabled) {
            bEditing = true;
        }
        else {
            bEditing = false;
        }
    }
    else if (e.target == gui_triggerBeginButton) {

        if(e.enabled) {
            animations.begin();
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
    gui_brightness = folder->addSlider("Brightness", 0, 1, 0.4f);
    gui_colour = folder->addColorPicker("Colour", ofColor(255,0,255));
    folder->onColorPickerEvent(this, &ofApp::onColorPickerEvent);

    folder->expand();

    gui->addHeader("LIGHT SETTINGS");
    gui->addFooter();
    gui->setPosition(ofGetWidth() - gui->getWidth(), 0);

    gui_editLabel = gui->addLabel("");
    gui_playButton = gui->addToggle("PLAYING",true);
    gui_editButton = gui->addToggle("Edit Mode",false);
    gui_showImageButton = gui->addToggle("Show Background Animation (i)",true);
    gui_triggerBeginButton = gui->addButton("Trigger Animation Start (b)");
    gui_nextAnimationButton = gui->addButton("Trigger Next Animation (n)");
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


