#pragma once

#include "ofMain.h"
#include "ofxArtnet.h"
#include "ofxDatGui.h"
#include "LightsEditor.h"
#include "TreeData.h"
#include "GuiMap.h"
#include "Animations.h"

#include "ofxGenericDmx.h"
#define DMX_DATA_LENGTH 513

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

            void updateTreeDMX(int i);
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

        /* Enntec DMX USB Pro object */
        DmxDevice* dmxInterface_;
        //our DMX packet (which holds the channel values + 1st byte for the start code)
        unsigned char dmxData_[DMX_DATA_LENGTH];
        bool bDmxUsbActive;

        /* Animations */
        Animations animations;
        float curTimeTree, prevTimeTree;
        float wait_time;

        /* GUI */
        ofxDatGui* gui;
        ofxDatGuiColorPicker *gui_colour;
        ofxDatGuiSlider *gui_brightness;
        GuiMap guiMap;
        ofxDatGuiToggle* gui_playButton;
        ofxDatGuiLabel* gui_editLabel;
        ofxDatGuiToggle* gui_showImageButton;
        ofxDatGuiFolder* paramfolder;
        bool bEditing;
};
