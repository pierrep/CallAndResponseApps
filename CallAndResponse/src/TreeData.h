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
        enum State {LIGHTS_OFF, LIGHTS_ON };
        State state;
        bool isPlaying;
        bool bShowBgImage;

        vector<Tree *> trees;
        unsigned int currentTree;
        unsigned int currentLight;
        unsigned int nextTree;
        unsigned int targetTree;

        ofColor colour;
        float brightness;
        float pixelWidth;

    protected:

        ofxXmlSettings xml;


    private:
};
