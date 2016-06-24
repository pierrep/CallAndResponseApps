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
        enum State {LIGHTS_OFF, LIGHTS_ON, START_TRAIL, END_TRAIL, START_BLOOM, END_BLOOM, NEW_TREE, NEXT_TREE };
        State state;
        bool isPlaying;
        bool bShowBgImage;

        vector<Tree *> trees;
        unsigned int currentTree;
        unsigned int currentLight;
        unsigned int nextTree;
        unsigned int targetTree;
        int direction;

        ofColor colour;
        float brightness;
        float pixelWidth;

    protected:

        ofxXmlSettings xml;


    private:
};
