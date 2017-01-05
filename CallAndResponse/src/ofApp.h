#pragma once

#include "ofMain.h"


#if !defined(TARGET_RASPBERRY_PI)
#define USE_GUI 1
#endif

#include "ofxArtnet.h"

#ifdef USE_GUI
#include "ofxDatGui.h"
#endif

#include "ofxOscParameterSync.h"
#include "LightsEditor.h"
#include "TreeData.h"
#include "GuiMap.h"
#include "Animations.h"
#include "ofxMarkovChain.h"


#define USE_USB_DMX

#ifdef USE_USB_DMX
	#ifdef TARGET_WIN32
		#include "ofxDmx.h"
	#else
		#include "ofxGenericDmx.h"
	#endif
#endif

#define DMX_DATA_LENGTH 513

class ofApp : public ofBaseApp{

    public:
            ofApp();
            void setup();
            void setupGui();
            void update();
            void draw();
            void exit();
            void keyPressed(int key);
            void keyReleased(int key);
            void mouseMoved(int x, int y );
            void mouseDragged(int x, int y, int button);
            void mousePressed(int x, int y, int button);
            void mouseReleased(int x, int y, int button);
            void mouseEntered(int x, int y);
            void mouseExited(int x, int y);
            void windowResized(int w, int h);
            void dragEvent(ofDragInfo dragInfo);
            void gotMessage(ofMessage msg);

            void setupDMX();
            void sendTreeDMX(int i);
            void clearTrees();
            void resetTrees();
            void drawModel();
#ifdef USE_GUI
            //void onButtonEvent(ofxDatGuiButtonEvent e);
            void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
#endif
            void processState();
            void bloomTree();            
            unsigned int  getNextTree();
            unsigned int  calculateDestinationTree();
			void calculateOtherBlooms();
			int getQuadrant();
            void onKeyframe(ofxPlaylistEventArgs& args);
            void mousePositionChanged(ofVec2f & mousePosition);
            void TriggerAnimationBegin(bool &val);
            void TriggerNextAnimation(bool &val);
			void checkForShutdown();

        /* Trees */
        LightsEditor editor;
        TreeData data;

        /* ArtNet */
        ofxArtnet artnet;
        bool bArtNetActive;

        /* Enntec DMX USB Pro object */
#ifdef USE_USB_DMX
	#ifdef TARGET_WIN32
		ofxDmx dmxInterface;
	#else
		DmxDevice* dmxInterface;
		unsigned char dmxData[DMX_DATA_LENGTH];
	#endif
#endif
        bool bDmxUsbActive;

        /* Audio pings */
        ofSoundPlayer ping;

        /* Animations */
        Animations animations;
        float curTimeTree, prevTimeTree;
        ofxPlaylist timeline;
        float playhead;
        int bloomCount;
        ofxMC::MarkovChain markov;

        /* Global Constants */
        const float gBloomTime;
        const float gTrailTime;
        const float gPauseTime;
        string      gIPAddress;
        string      gHOST_IPAddress;
        string      gStorm_IPAddress;

        /* GUI */
#ifdef USE_GUI
        ofxDatGui* gui;
        ofxDatGuiColorPicker*   gui_colour;
        ofxDatGuiButton*        gui_triggerBeginButton;
        ofxDatGuiButton*        gui_nextAnimationButton;
        ofxDatGuiFolder*        paramfolder;
#endif
        GuiMap guiMap;

        ofxOscParameterSync sync;
        bool bHost;
};
