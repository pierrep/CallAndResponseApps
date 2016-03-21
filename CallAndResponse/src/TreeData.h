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
        int currentTree;
        int currentLight;

        ofColor colour;
        float brightness;

    protected:

        ofxXmlSettings xml;


    private:
};
