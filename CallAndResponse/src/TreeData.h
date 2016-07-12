#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

class Tree;

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
        ofParameter<int>    currentLight;
        ofParameter<int>    currentTree;
        ofParameter<int>    nextTree;
        ofParameter<int>    targetTree;
        ofParameter<ofVec2f> lightPosition;
        ofParameter<ofVec2f> mousePosition;

        void lightPositionChanged(ofVec2f & lightPosition);

        vector<Tree *> trees;
        int direction;

        ofColor colour;
        const float pixelWidth;

    protected:

        ofxXmlSettings xml;


    private:
};
