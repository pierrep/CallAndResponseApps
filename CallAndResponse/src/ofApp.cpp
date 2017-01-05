#include "ofApp.h"
#include "Tree.h"
#include "ofxPlaylist.h"
#include "LedFixture.h"

/* export MAKEFLAGS=-j3 */

using namespace Playlist;

ofApp::ofApp() :
    bloomCount(0),
    gBloomTime(7500.0f),
    gTrailTime(2100.0f),
    gPauseTime(1500.0f),
    gIPAddress("192.168.0.43"),
    //gIPAddress("192.168.2.16"),
    //gIPAddress("localhost"),
    gHOST_IPAddress("192.168.0.3"),
    //gHOST_IPAddress("192.168.2.15"),
    //gHOST_IPAddress("localhost"),
    gStorm_IPAddress("192.168.0.11"),
    bHost(true)
{

}

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(50,50,50);
    ofSetVerticalSync(false);
    ofSetFrameRate(25);

    data.load();
    editor.setup(&data);
    animations.setup(&data);
    animations.load();
    setupDMX();

#ifdef USE_GUI
    guiMap.setup(&data);
    setupGui();
    ping.load("ping.mp3");
#endif

    /* set up markov chain */
    ofLogNotice() << "Setting up Markov chain...";
    ofxMC::Matrix mat("transitionMatrix.txt");
    markov.setup(mat, 0);

    /* Set up timer */
    curTimeTree = ofGetElapsedTimeMillis();
    prevTimeTree = curTimeTree;

    /* setup callbacks */
    ofLogNotice() << "Setting up callbacks...";
    data.mousePosition.addListener(this, &ofApp::mousePositionChanged);
    data.bBeginAnimation.addListener(this,&ofApp::TriggerAnimationBegin);
    data.bNextAnimation.addListener(this,&ofApp::TriggerNextAnimation);

    /* Parameter Sync setup */
    ofLogNotice() << "Setting up parameter sync...";
    if(bHost) {
        sync.setup(data.parameters,6666,gIPAddress,6667);
    } else {
        sync.setup(data.parameters,6667,gHOST_IPAddress,6666);
    }

    /* Playlist setup */
    if(bHost) {
        ofLogNotice() << "Setting up playlist...";
        playhead = 0.0f;
        ofxKeyframeAnimRegisterEvents(this);
        timeline.addKeyFrame(Action::tween(gBloomTime, &playhead, 1.0f,TWEEN_LIN,TWEEN_EASE_OUT));
        timeline.addKeyFrame(Action::event(this,"END_BLOOM"));
    }

    /* Perform first bloom */
    if(bHost) {
        ofLogVerbose() << "Start Bloom\t time: " << ofGetElapsedTimeMillis() << " current tree: " << data.currentTree << " target tree: " << data.targetTree;
        data.currentTree = data.nextTree;
        bloomTree();
    }
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
		#ifndef TARGET_WIN32
		shared_ptr<ofOpenALSoundPlayer> player = dynamic_pointer_cast<ofOpenALSoundPlayer>(ping.getPlayer());
        player->close();
		#endif
    #endif

}

//--------------------------------------------------------------
void ofApp::bloomTree()
{    
    if(data.currentTree == data.targetTree) {
        ofLogNotice() << "Bloom Tree: " << data.currentTree << " Time: " << ofGetHours() << ":" << ofGetMinutes() << ":" << ofGetSeconds();
		
        /* play bellbird sound */
        //data.trees[data.currentTree]->playPing();

        /* set bloom effect */
        animations.clearActiveEffects();
		if (ofRandomf() > 0.0f) {
			animations.enableEffect("bloom");
			animations.enableEffect("line2");
		}
		else {
			animations.enableEffect("image pan");
		}
		calculateOtherBlooms();

    } else {
        /* set light trails */
        //animations.enableEffect("line");
        animations.enableEffect("trail particles");
    }

    if(!data.bEditMode) {
        animations.begin();
    }

}

//--------------------------------------------------------------
void ofApp::calculateOtherBlooms()
{
	int currentQuad = getQuadrant();
	if (currentQuad == 1) {
		data.tree2 = (int)ofRandom(3, 8);
		data.tree3 = (int)ofRandom(8, 13);
		data.tree4 = (int)ofRandom(13, 17);
	}
	else if (currentQuad == 2) {
		data.tree2 = (int)ofRandom(0, 3);
		data.tree3 = (int)ofRandom(8, 13);
		data.tree4 = (int)ofRandom(13, 17);
	}
	else if (currentQuad == 3) {
		data.tree2 = (int)ofRandom(0, 3);
		data.tree3 = (int)ofRandom(3, 8);
		data.tree4 = (int)ofRandom(13, 17);
	}
	else if (currentQuad == 4) {
		data.tree2 = (int)ofRandom(0, 3);
		data.tree3 = (int)ofRandom(3, 8);
		data.tree4 = (int)ofRandom(8, 13);
	} 
}

//--------------------------------------------------------------
int ofApp::getQuadrant()
{
	int quadrant = -1;

	// Quadrant 1 = 0,1,2
	// Quadrant 2 = 3,4,5,6,7
	// Quadrant 3 = 8,9,10,11,12
	// Quadrant 4 = 13,14,15,16
	switch (data.currentTree) {
		case 0:
		case 1:
		case 2:
			quadrant = 1;
			break;
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			quadrant = 2;
			break;
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
			quadrant = 3;
			break;
		case 13:
		case 14:
		case 15:
		case 16:
			quadrant = 4;
			break;
		default:
			break;
	}
	return quadrant;
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
    if(ofGetFrameNum()%30 == 0) {
        ofLogWarning() << "FPS: " << ofGetFrameRate();
    }

    if(data.bToggleEditMode != data.bEditMode) {
        if(data.bToggleEditMode) {
            data.bEditMode = true;
            editor.enableEditing();
        #ifdef USE_GUI
            gui->collapse();
        #endif
            data.currentTree = 0;
        } else {
            data.bEditMode = false;
            editor.disableEditing();
            animations.clearActiveEffects();
            animations.enableEffect("calibrate");
        #ifdef USE_GUI
            gui->expand();
        #endif
        }
    }

    if(data.bTogglePlaying != data.bIsPlaying) {
        if(data.bTogglePlaying) {
            data.bIsPlaying = true;
            data.state = data.END_TRAIL;
            resetTrees();
            timeline.clear();
        } else {
            data.bIsPlaying = false;
            data.lastState = data.state;
            data.state = data.PAUSED;
            resetTrees();
            timeline.clear();
        }
    }

    switch (data.state)
    {
        case data.START_BLOOM:
        {
            ofLogVerbose() << " ";
            ofLogVerbose() << "Start Bloom\t time: " << ofGetElapsedTimeMillis() << " current tree: " << data.currentTree << " target tree: " << data.targetTree;

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
            ofLogVerbose() << "End Bloom  \t time: " << ofGetElapsedTimeMillis() << " current tree: " << data.currentTree << " target tree: " << data.targetTree;
            if(data.bIsPlaying) {
                data.state = data.LIGHTS_OFF;
            }
            data.trees[data.currentTree]->clear();
			data.trees[data.tree2]->clear();
			data.trees[data.tree3]->clear();
			data.trees[data.tree4]->clear();
            animations.clearActiveEffects();
			data.tree2 = -1;
			data.tree3 = -1;
			data.tree4 = -1;

            playhead = 0.0f;
            bloomCount++;
            if(bloomCount == 2) {
                ofLogVerbose() << "End call & response...start a new one.";
                timeline.addKeyFrame(Action::pause(gPauseTime));
                data.targetTree = calculateDestinationTree();
                float val = ofRandom(0,1);
                if(val < 0.5f) data.direction = -1;
                else data.direction = 1;
                ofLogVerbose() << " Direction = " << data.direction;
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
            ofLogVerbose() << " Direction = " << data.direction;

            data.nextTree = getNextTree();
            timeline.addKeyFrame(Action::event(this,"START_TRAIL"));
            break;
        }
        case data.START_TRAIL:
        {
			ofLogNotice() << "Trail:" << data.currentTree;
            ofLogVerbose() << "Start Trail\t time: " << ofGetElapsedTimeMillis() << " current tree: " << data.currentTree << " target tree: " << data.targetTree;

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
            ofLogVerbose() << "End Trail  \t time: " << ofGetElapsedTimeMillis() << " current tree: " << data.currentTree << " target tree: " << data.targetTree;
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
        case data.PAUSED:
        default:
        {
            break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::checkForShutdown()
{
#ifdef TARGET_WIN32
	if ((ofGetHours() >= 23) && (ofGetMinutes() >= 30)) ofSystem("shutdown -s -t 01");
#endif
}

//--------------------------------------------------------------
void ofApp::update(){
	checkForShutdown();

    sync.update();
    timeline.update();

    processState();

	animations.updateFBO();

    if(!data.bEditMode) {
        animations.update(playhead);
    }

#ifdef USE_GUI
    data.colour = gui_colour->getColor();
#endif

    for(unsigned int i = 0;i < data.trees.size();i++)
    {
        data.trees[i]->update();

        #ifdef USE_GUI
        if(data.trees[i]->getBufferPixels()[499] > 0) {
            ping.play();
        }
        #endif
        sendTreeDMX(i);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
	#ifdef USE_GUI
    if(data.bEditMode) {
        ofSetWindowTitle( "EDITING: X = "+ofToString(mouseX)+" Y = "+ofToString(mouseY));
    } else {
        if(bHost) ofSetWindowTitle( "HOST  state: "+ ofToString(data.state)  );
        else ofSetWindowTitle( "CLIENT  state: "+ ofToString(data.state)  );
    }
    #endif	

#ifdef USE_GUI
    animations.draw(400,0);
    editor.draw(400,0,1200,900);
    guiMap.draw(0,0,400,900);
    animations.drawGui();

    /* draw raw tree LED output */
    if(data.bShowBgImage) {
        for(unsigned int i = 0;i < data.trees.size();i++)
        {
            data.trees[i]->draw(400,i*50);
        }
    }
#endif


}

//--------------------------------------------------------------
void ofApp::sendTreeDMX(int i)
{
    if(bArtNetActive) {
        //if(data.trees[i]->isDirty())
        {
            artnet.sendDmx(gStorm_IPAddress, 0, data.trees[i]->getId(), data.trees[i]->getBufferPixels(), 512);
        }
    }
#ifdef USE_USB_DMX
	else if (bDmxUsbActive) {
	#ifdef TARGET_WIN32
		/* only send current tree */
		if (data.currentTree == i) { 
			for (int j = 0; j < DMX_DATA_LENGTH-1; j++) {
				dmxInterface.setLevel(j+1, data.trees[i]->getBufferPixels()[j]);
			}
			dmxInterface.update();
		}
	#else
		/* only send current tree */
		if (data.currentTree == i) {
			dmxData[0] = 0;
			memcpy(&dmxData[1], data.trees[i]->getBufferPixels(), 512);
			dmxInterface->writeDmx(dmxData, DMX_DATA_LENGTH);
		}

	#endif
	}
#endif

}

//--------------------------------------------------------------
void ofApp::clearTrees()
{
    for(unsigned int i = 0;i < data.trees.size();i++)
    {
        data.trees[i]->clear();
    }
}

//--------------------------------------------------------------
void ofApp::resetTrees()
{
    clearTrees();
    for(unsigned int i = 0;i < data.trees.size();i++)
    {
        sendTreeDMX(i);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if((key == 'f') || (key == 'F')) {
        ofToggleFullscreen();
    }


    if(key == 'e') {
        data.bToggleEditMode = !data.bToggleEditMode;
    }
    if(key == ' ') {
        data.bTogglePlaying = !data.bTogglePlaying;
    }
#ifdef USE_GUI
    if(key == 'i') {
         data.bShowBgImage = !data.bShowBgImage;
    }
#endif

    if(key == '1') animations.setPattern(1);
    else if(key == '2') animations.setPattern(2);
    else if(key == '3') animations.setPattern(3);
    else if(key == '4')
    {
        animations.setPattern(4);

        for(unsigned int i = 0;i < data.trees[data.currentTree]->lights.size();i++)
        {
            data.trees[data.currentTree]->lights[i]->setColour(ofColor::red);
            data.trees[data.currentTree]->lights[i]->fadeOn(5000.0f);
        }
    }
    else if(key == '5') animations.setPattern(5);


    if(key == 'n') {
        data.bNextAnimation = !data.bNextAnimation;
    }
    if(key == 'b') {
        data.bBeginAnimation = !data.bBeginAnimation;
    }
}

//--------------------------------------------------------------
void ofApp::TriggerNextAnimation(bool & val)
{
    clearTrees();
    animations.nextEffect();
}

//--------------------------------------------------------------
void ofApp::TriggerAnimationBegin(bool & val)
{
    clearTrees();
    animations.begin();
}

//--------------------------------------------------------------
void ofApp::mousePositionChanged(ofVec2f & mousePosition)
{
    if(bHost)
    {
        animations.updateActiveEffectPos(mousePosition);
    }

}

#ifdef USE_GUI
//void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
//{

//    if (e.target == gui_triggerBeginButton) {

//        if(e.enabled) {
//            animations.begin();
//        }
//    }

//}

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
    ofxDatGui::setAssetPath("../../../../../addons/ofxDatGui/");
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );    
    gui->addHeader("LIGHT SETTINGS");
    gui->addFRM();
    gui->addFooter();
    gui->setPosition(ofGetWidth() - gui->getWidth(), 0);

    ofxDatGuiFolder* folder = gui->addFolder("Master Controls", ofColor::green);
    gui_colour = folder->addColorPicker("Colour", ofColor(255,0,255));
    folder->onColorPickerEvent(this,&ofApp::onColorPickerEvent);

    gui->addBreak();

    ofxDatGuiFolder* lightFolder = gui->addFolder("Sequence Controls", ofColor::blue);

    ofParameterGroup& p = data.parameters;

    for(int i = 0; i < p.size();i++) {
        if((p.getType(i) == "11ofParameterIfE") || (p.getType(i) == "class ofParameter<float>")) {
            lightFolder->addSlider(p.getFloat(i));
        }
        else if((p.getType(i) == "11ofParameterIiE") || (p.getType(i) == "class ofParameter<int>")) {
            lightFolder->addSlider(p.getInt(i));
        }
        else if((p.getType(i) == "11ofParameterIbE") || (p.getType(i) == "class ofParameter<bool>")) {
            lightFolder->addToggle(p.getBool(i));
        }
    }

    lightFolder->expand();

    //gui_triggerBeginButton = gui->addButton("Trigger Animation Start (b)");
    //gui_nextAnimationButton = gui->addButton("Trigger Next Animation (n)");
    //gui->onButtonEvent(this, &ofApp::onButtonEvent);
    gui->addBreak();

}

#endif

//--------------------------------------------------------------
void ofApp::setupDMX()
{
    if(bHost) {
        ofLogNotice() << "Setup Artnet DMX...";
        bArtNetActive = artnet.setup(gHOST_IPAddress.c_str()); //make sure the firewall is deactivated at this point
    } else {
        bArtNetActive = artnet.setup(gIPAddress.c_str()); //make sure the firewall is deactivated at this point
    }

    if(!bArtNetActive) {
		ofLogError() << "ArtNet failed to setup.";
#ifdef USE_USB_DMX
		ofLogNotice() << "Setup USB DMX...";
	#ifdef TARGET_WIN32
		if (dmxInterface.connect(0, 512)) {
			ofLogNotice("DMX USB opened...");
			bDmxUsbActive = true;
		}
		else {
			ofLog(OF_LOG_ERROR, "No Enttec Device Found");
			bDmxUsbActive = false;
		}
	#else
		memset(dmxData, 0, DMX_DATA_LENGTH);
		dmxInterface = ofxGenericDmx::openFirstDevice();
		if (dmxInterface == 0) {
			ofLog(OF_LOG_ERROR, "No Enttec Device Found");
			bDmxUsbActive = false;
		}
		else {
			ofLogNotice("DMX USB opened...");
			bDmxUsbActive = true;
		}
	#endif

#endif
    }
    resetTrees();
}

//--------------------------------------------------------------
unsigned int ofApp::calculateDestinationTree()
{

    markov.update();
    unsigned int tree = markov.getState();

    ofLogNotice() << "New target tree: " << tree << " (current tree: " << data.currentTree <<")";
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

    ofLogVerbose() << " getNextTree = " << tree;
    return tree;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    if(!bHost)
    {
        data.mousePosition = ofVec2f(x,y);
    }
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
