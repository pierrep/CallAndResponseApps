#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxArtnet.h"
//#include "ofxGui.h"
#include "ofxDatGui.h"
#include "LightsEditor.h"
#include "TreeData.h"
#include "GuiMap.h"
#include "Animations.h"

class ofApp : public ofBaseApp{

    public:
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

            void clearTrees();
            void drawModel();
            void onButtonEvent(ofxDatGuiButtonEvent e);
            void onColorPickerEvent(ofxDatGuiColorPickerEvent e);

        /* Trees */
        LightsEditor editor;
        TreeData data;

        /* ArtNet */
        ofxArtnet artnet;
        bool bArtNetActive;

        /* Animations */
        Animations animations;
        float curTimeTree, prevTimeTree;
        float wait_time;

        /* GUI */
        //ofParameter<float> brightness;
//        ofParameter<ofColor> colour;
//        ofParameterGroup parameters;
        //ofxPanel gui;
        ofxDatGui* gui;
        ofxDatGuiColorPicker *gui_colour;
        ofxDatGuiSlider *gui_brightness;
        GuiMap guiMap;
        ofxDatGuiToggle* gui_playButton;
        ofxDatGuiToggle* gui_showImageButton;
};
