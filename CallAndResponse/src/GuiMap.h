#pragma once

#include "ofMain.h"
#include "TreeData.h"

class GuiMap
{
    public:
        GuiMap();
        ~GuiMap();
        void setup(TreeData* data);
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

        ofImage mapImg;
        TreeData* data;
        float circleRadius;
        ofFbo   fbo;

    private:
};
