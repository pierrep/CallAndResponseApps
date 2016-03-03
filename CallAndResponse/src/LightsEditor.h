#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "Tree.h"

class LightsEditor
{
    public:
        LightsEditor();
        ~LightsEditor();
        void setup();
        void draw();
        void load(vector<Tree *> * trees);
        void mousePressed(ofMouseEventArgs& args);
        void mouseDragged(ofMouseEventArgs& args);
        void keyPressed(ofKeyEventArgs& args);

    protected:

        ofxXmlSettings xml;
        ofImage treeimg;
        int currentLight;
        int currentTree;
        vector<Tree *> * trees;

        float circleRadius;

    private:
};
