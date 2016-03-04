#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "Tree.h"

class LightsEditor
{
    public:
        LightsEditor();
        ~LightsEditor();
        void setup(vector<Tree *> * _trees);
        void draw();
        void draw(float x, float y, float w, float  h);
        void mousePressed(ofMouseEventArgs& args);
        void mouseDragged(ofMouseEventArgs& args);
        void mouseMoved(ofMouseEventArgs& args);
        void mouseReleased(ofMouseEventArgs& args);
        void keyPressed(ofKeyEventArgs& args);

        void enableMouseEvents();
        void disableMouseEvents();
        void enableKeyEvents();
        void disableKeyEvents();

    protected:

        ofxXmlSettings xml;
        ofImage treeimg;
        int currentLight;
        int currentTree;
        vector<Tree *> * trees;
        float circleRadius;
        ofFbo   fbo;

    private:
};
