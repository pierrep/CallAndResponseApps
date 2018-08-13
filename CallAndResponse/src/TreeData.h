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

        ofParameterGroup    parameters;
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
        ofParameter<int>    animationType;
        ofParameter<bool>   bChangeAnimation;
        ofParameter<bool>   bMoveForward;
        ofParameter<bool>   bMoveBack;
        ofParameter<ofColor> colour;


        void lightPositionChanged(ofVec2f & lightPosition);
        ofColor getRandomPaletteColour();
        ofColor getRandomPaletteColourX(int y);
        ofColor setSimilarPaletteColour(ofColor c,float offset);

        vector<Tree *> trees;
        int direction;
        ofParameter<int> tree2;
        ofParameter<int> tree3;
        ofParameter<int> tree4;
        int previousTree;

        size_t currentPaletteImage;
        vector<ofImage> paletteImage;
        size_t numPaletteImgs;

        const float pixelWidth;
        bool bUseFrameBuffer;

    protected:

        ofxXmlSettings xml;


    private:
};
