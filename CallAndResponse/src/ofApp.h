#pragma once

#include "ofMain.h"

#ifdef TARGET_LINUX
#define USE_GUI 1
#endif

#include "ofxArtnet.h"

#ifdef USE_GUI
#include "ofxDatGui.h"
#endif

#include "LightsEditor.h"
#include "TreeData.h"
#include "GuiMap.h"
#include "Animations.h"
#include "ofxMarkovChain.h"

#ifdef USE_USB_DMX
#include "ofxGenericDmx.h"
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
            void onButtonEvent(ofxDatGuiButtonEvent e);
            void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
#endif
            void processState();
            void bloomTree();            
            int  getNextTree();
            int  calculateDestinationTree();
            void onKeyframe(ofxPlaylistEventArgs& args);

        /* Trees */
        LightsEditor editor;
        TreeData data;

        /* ArtNet */
        ofxArtnet artnet;
        bool bArtNetActive;

        /* Enntec DMX USB Pro object */
#ifdef USE_USB_DMX
        DmxDevice* dmxInterface_;
        //our DMX packet (which holds the channel values + 1st byte for the start code)
        unsigned char dmxData_[DMX_DATA_LENGTH];
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
        string gIPAddress;


        /* GUI */
#ifdef USE_GUI
        ofxDatGui* gui;
        ofxDatGuiColorPicker *gui_colour;
        ofxDatGuiSlider *gui_brightness;
        ofxDatGuiToggle* gui_playButton;
        ofxDatGuiToggle* gui_editButton;
        ofxDatGuiLabel* gui_editLabel;
        ofxDatGuiToggle* gui_showImageButton;
        ofxDatGuiButton* gui_triggerBeginButton;
        ofxDatGuiButton* gui_nextAnimationButton;
        ofxDatGuiFolder* paramfolder;
#endif
        GuiMap guiMap;
        bool bEditing;
};
