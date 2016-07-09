#pragma once
#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxOscParameterSync.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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

        void onButtonEvent(ofxDatGuiButtonEvent e);
        void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
        void setupGui();

        ofxOscParameterSync     sync;

        ofParameterGroup        parameters;

        ofParameter<ofColor>    paramColour;
        ofParameter<float>      paramBrightness;
        ofParameter<bool>       paramPlayButton;
        ofParameter<bool>       paramEditButton;
        ofParameter<bool>       paramShowImageButton;
        ofParameter<bool>       paramTriggerBeginButton;
        ofParameter<bool>       paramNextAnimButton;

        ofxDatGui* gui;
        ofxDatGuiFolder*        folder;
        ofxDatGuiColorPicker*   gui_colour;
        ofxDatGuiSlider*        gui_brightness;
        ofxDatGuiToggle*        gui_playButton;
        ofxDatGuiToggle*        gui_editButton;
        ofxDatGuiLabel*         gui_editLabel;
        ofxDatGuiToggle*        gui_showImageButton;
        ofxDatGuiButton*        gui_triggerBeginButton;
        ofxDatGuiButton*        gui_nextAnimationButton;
};
