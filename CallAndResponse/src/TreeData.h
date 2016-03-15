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

        vector<Tree *> trees;
        int currentTree;

    protected:

        ofxXmlSettings xml;


    private:
};
