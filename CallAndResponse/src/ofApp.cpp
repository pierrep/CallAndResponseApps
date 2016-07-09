#include "ofApp.h"
#include "Tree.h"
#include "ofxPlaylist.h"
#include "LedFixture.h"

using namespace Playlist;

ofApp::ofApp() :
    bloomCount(0),
    gBloomTime(7500.0f),
    gTrailTime(900.0f),
    gPauseTime(1500.0f),
    gIPAddress("192.168.0.2"),
    bEditing(false)
{

}

//--------------------------------------------------------------
void ofApp::setupDMX()
{
    bArtNetActive = true;
    artnet.setup(gIPAddress.c_str()); //make sure the firewall is deactivated at this point
    if(!bArtNetActive) {
#ifdef USE_USB_DMX
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
#endif
    }
    resetTrees();
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(50,50,50);
    ofSetVerticalSync(false);
    ofSetFrameRate(30);
    ofSetLogLevel(OF_LOG_NOTICE);

    data.load();
    editor.setup(&data);
    guiMap.setup(&data);
    animations.setup(&data);
    animations.load();

#ifdef USE_GUI
    setupGui();
    ping.load("ping.mp3");
#endif

    /* set up markov chain */
    ofxMC::Matrix mat("transitionMatrix.txt");
    markov.setup(mat, 0);

    /* Set up timer */
    curTimeTree = ofGetElapsedTimeMillis();
    prevTimeTree = curTimeTree;

    /* Set Global Brightness */
    data.brightness = 0.5f;
    sync.setup(data.parameters,6666,"localhost",6667);

    /* Playlist setup */
    playhead = 0.0f;    
    ofxKeyframeAnimRegisterEvents(this);
    timeline.addKeyFrame(Action::tween(gBloomTime, &playhead, 1.0f,TWEEN_LIN,TWEEN_EASE_OUT));
    timeline.addKeyFrame(Action::event(this,"END_BLOOM"));

    /* Perform first bloom */
    ofLogNotice() << "Start Bloom\t time: " << ofGetElapsedTimeMillis() << " current tree: " << data.currentTree << " target tree: " << data.targetTree;
    data.currentTree = data.nextTree;
    bloomTree();
}

//--------------------------------------------------------------
void ofApp::exit(){
    ofLogNotice() << "Exiting...";
    data.save();
    animations.clearActiveEffects();
    animations.save();
    resetTrees();

    #ifdef USE_GUI
        ping.unload();
        shared_ptr<ofOpenALSoundPlayer> player = dynamic_pointer_cast<ofOpenALSoundPlayer>(ping.getPlayer());
        player->close();
    #endif

}

//--------------------------------------------------------------
void ofApp::bloomTree()
{

    if(data.currentTree == data.targetTree) {
        /* play bellbird sound */
        data.trees[data.currentTree]->playPing();

        /* set bloom effect */
        animations.clearActiveEffects();
        animations.enableEffect("bloom");
        animations.enableEffect("line2");

    } else {
        /* set light trails */
        animations.clearActiveEffects();
        animations.enableEffect("line");
    }

    if(!editor.isEditing()) {
        animations.begin();
    }

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

            if(data.bIsPlaying) {
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
            if(data.bIsPlaying) {
                data.state = data.LIGHTS_OFF;
            }
            data.trees[data.currentTree]->clear();

            playhead = 0.0f;
            bloomCount++;
            if(bloomCount == 2) {
                ofLogNotice() << "End call & response...start a new one.";
                timeline.addKeyFrame(Action::pause(gPauseTime));
                data.targetTree = calculateDestinationTree();
                float val = ofRandom(0,1);
                if(val < 0.5f) data.direction = -1;
                else data.direction = 1;
                ofLogNotice() << " Direction = " << data.direction;
                data.currentTree = data.targetTree;
                data.nextTree = data.currentTree;
                timeline.addKeyFrame(Action::event(this,"START_BLOOM"));
                bloomCount = 0;
                return;
            }

            data.targetTree = calculateDestinationTree();
            float val = ofRandom(0,1);
            if(val < 0.5f) data.direction = -1;
            else data.direction = 1;
            ofLogNotice() << " Direction = " << data.direction;

            data.nextTree = getNextTree();
            timeline.addKeyFrame(Action::event(this,"START_TRAIL"));
            break;
        }
        case data.START_TRAIL:
        {
            ofLogNotice() << "Start Trail\t time: " << ofGetElapsedTimeMillis() << " current tree: " << data.currentTree << " target tree: " << data.targetTree;

            if(data.bIsPlaying) {
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
            if(data.bIsPlaying) {
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
    sync.update();
    timeline.update();

    processState();


    if(data.state == data.LIGHTS_OFF) return;

    if(!editor.isEditing()) {
        animations.update(playhead);
    }

#ifdef USE_GUI
    data.colour = gui_colour->getColor();
    data.brightness = gui_brightness->getValue();
#endif

    for(unsigned int i = 0;i < data.trees.size();i++)
    {
        data.trees[i]->update();
        //int universe = data.trees[i]->getId();
        #ifdef USE_GUI
        if(data.trees[i]->getBufferPixels()[509] > 128) {
            //ping.play();
        }
        #endif
        sendTreeDMX(i);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
	#ifdef USE_GUI
    ofSetWindowTitle("X = "+ofToString(mouseX)+" Y = "+ofToString(mouseY) + " fps:"+ofToString(ofGetFrameRate()));
    #endif	

    animations.updateFBO();

    guiMap.draw(0,0,400,900);
    animations.draw(400,0);
    editor.draw(400,0,1200,900);
    animations.drawGui();

    /* draw raw tree LED output */
    if(data.bShowBgImage) {
        for(unsigned int i = 0;i < data.trees.size();i++)
        {
            data.trees[i]->draw(400,i*50);
        }
    }

}

//--------------------------------------------------------------
void ofApp::sendTreeDMX(int i)
{
    if(bArtNetActive) {
        if(data.trees[i]->isDirty()) {
            artnet.sendDmx("192.168.0.11", 0, data.trees[i]->getId(), data.trees[i]->getBufferPixels(), 512);
        }
    }
    else if(bDmxUsbActive) {
#ifdef USE_USB_DMX
        if(i == 0) { //only send 1st tree
        dmxData_[0] = 0;
        memcpy(&dmxData_[1],data.trees[i]->getBufferPixels(),512);
        dmxInterface_->writeDmx( dmxData_, DMX_DATA_LENGTH );
        }
#endif
    }
}

//--------------------------------------------------------------
void ofApp::clearTrees()
{
    for(int i = 0;i < data.trees.size();i++)
    {
        data.trees[i]->clear();
    }
}

//--------------------------------------------------------------
void ofApp::resetTrees()
{
    clearTrees();
    for(int i = 0;i < data.trees.size();i++)
    {
        sendTreeDMX(i);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if((key == 'f') || (key == 'F')) {
        ofToggleFullscreen();
    }

#ifdef USE_GUI
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
            data.bIsPlaying = false;
        } else {
            gui_playButton->setLabel("PLAYING");
            data.bIsPlaying = true;
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
#endif

    if(key == '1') animations.setPattern(1);
    else if(key == '2') animations.setPattern(2);
    else if(key == '3') animations.setPattern(3);
    else if(key == '4')
    {
        animations.setPattern(4);

        for(int i = 0;i < data.trees[data.currentTree]->lights.size();i++)
        {
            data.trees[data.currentTree]->lights[i]->setColour(ofColor::red);
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

#ifdef USE_GUI
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    if (e.target == gui_playButton){
        if(e.target->getLabel() == "PLAYING") {
            e.target->setLabel("PAUSED");
            data.bIsPlaying = false;
        } else if (e.target->getLabel() == "PAUSED") {
            e.target->setLabel("PLAYING");
            data.bIsPlaying = true;
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
    //gui_playButton = gui->addToggle("PLAYING",true);

    ofParameterGroup& p = data.parameters;

    for(int i = 0; i < p.size();i++) {
        if(p.getType(i) == "11ofParameterIfE") {
            gui->addSlider(p.getFloat(i));
        }
        else if(p.getType(i) == "11ofParameterIiE") {
            gui->addSlider(p.getInt(i));
        }
        else if(p.getType(i) == "11ofParameterIbE") {
            gui->addToggle(p.getBool(i));
        }
    }


    gui_editButton = gui->addToggle("Edit Mode",false);
    gui_showImageButton = gui->addToggle("Show Background Animation (i)",true);
    gui_triggerBeginButton = gui->addButton("Trigger Animation Start (b)");
    gui_nextAnimationButton = gui->addButton("Trigger Next Animation (n)");
    gui->onButtonEvent(this, &ofApp::onButtonEvent);

    gui->addBreak();

}

#endif

//--------------------------------------------------------------
unsigned int ofApp::calculateDestinationTree()
{

    markov.update();
    unsigned int tree = markov.getState();

    ofLogNotice() << "New target tree: " << tree << "(current tree: " << data.currentTree <<")";
    return tree;
}

//--------------------------------------------------------------
unsigned int ofApp::getNextTree()
{
    unsigned int tree = data.currentTree;

    if(data.direction == 1) {
        switch(tree) {
            case 0:     tree = 1; break;
            case 1:     tree = 2; break;
            case 2:     tree = 8; break;
            case 3:     tree = 0; break;
            case 4:     tree = 3; break;
            case 5:     tree = 4; break;
            case 6:     tree = 5; break;
            case 7:     tree = 6; break;
            case 8:     tree = 9; break;
            case 9:     tree = 10; break;
            case 10:    tree = 11; break;
            case 11:    tree = 12; break;
            case 12:    tree = 16; break;
            case 13:    tree = 7; break;
            case 14:    tree = 13; break;
            case 15:    tree = 14; break;
            case 16:    tree = 15; break;
        }
    }
    else if(data.direction == -1) {
        switch(tree) {
            case 0:     tree = 3; break;
            case 1:     tree = 0; break;
            case 2:     tree = 1; break;
            case 3:     tree = 4; break;
            case 4:     tree = 5; break;
            case 5:     tree = 6; break;
            case 6:     tree = 7; break;
            case 7:     tree = 13; break;
            case 8:     tree = 2; break;
            case 9:     tree = 8; break;
            case 10:    tree = 9; break;
            case 11:    tree = 10; break;
            case 12:    tree = 11; break;
            case 13:    tree = 14; break;
            case 14:    tree = 15; break;
            case 15:    tree = 16; break;
            case 16:    tree = 12; break;
        }
    }

    ofLogNotice() << " getNextTree = " << tree;
    return tree;
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
#ifdef USE_GUI
    gui->setPosition(ofGetWidth() - gui->getWidth(), 0);
#endif
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}


