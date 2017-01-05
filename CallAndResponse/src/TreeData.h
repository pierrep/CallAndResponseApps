#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

#include "Tree.h"

class TreeData
{
    public:
        TreeData();
        ~TreeData();
        void load();
        void save();

        /* State */
        enum State {LIGHTS_OFF, LIGHTS_ON, PAUSED, START_TRAIL, END_TRAIL, START_BLOOM, END_BLOOM, NEW_TREE, NEXT_TREE };
        State state;
        State lastState;

        ofParameterGroup parameters;
        ofParameter<float>  brightness;
        ofParameter<bool>   bIsPlaying;
        ofParameter<bool>   bTogglePlaying;
        ofParameter<bool>   bShowBgImage;
        ofParameter<bool>   bEditMode;
        ofParameter<bool>   bToggleEditMode;
        ofParameter<bool>   bBeginAnimation;
        ofParameter<bool>   bNextAnimation;
        ofParameter<int>    currentLight;
        ofParameter<int>    currentTree;
        ofParameter<int>    nextTree;
        ofParameter<int>    targetTree;
        ofParameter<ofVec2f> lightPosition;
        ofParameter<ofVec2f> mousePosition;

        void lightPositionChanged(ofVec2f & lightPosition);

        vector<Tree *> trees;
        int direction;
		int tree2;
		int tree3;
		int tree4;

        ofColor colour;
        const float pixelWidth;
        bool bUseFrameBuffer;

    protected:

        ofxXmlSettings xml;


    private:
};
