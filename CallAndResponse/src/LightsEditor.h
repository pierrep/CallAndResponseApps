#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

class TreeData;

class LightsEditor
{
    public:
        LightsEditor();
        ~LightsEditor();
        void setup(TreeData * _data);
        void draw();
        void draw(float x, float y, float w, float  h);
        void mousePressed(ofMouseEventArgs& args);
        void mouseDragged(ofMouseEventArgs& args);
        void mouseMoved(ofMouseEventArgs& args);
        void mouseReleased(ofMouseEventArgs& args);
        void keyPressed(ofKeyEventArgs& args);
        bool isEditing() {return bEditing;}

        void enableEditing();
        void disableEditing();

    protected:

        ofxXmlSettings xml;
        vector<ofImage> treeimg;
        int currentLight;
        int currentTree;
        TreeData * data;
        float circleRadius;
        ofTrueTypeFont lightNum;
        float editorWidth;
        float editorHeight;
        bool bEditing;

    private:
};
