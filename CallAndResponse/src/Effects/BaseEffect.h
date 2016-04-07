
#pragma once
#include "ofMain.h"

class BaseEffect
{
    public:

        BaseEffect();
        virtual ~BaseEffect() {};

        virtual void setup() = 0;
        virtual void draw() = 0;
        virtual void draw(float x, float y, float w, float h) = 0;
        virtual void update(float time) = 0;
        void enableEditing();
        void disableEditing();
        void mousePressed(ofMouseEventArgs& args);
        void mouseDragged(ofMouseEventArgs& args);
        void mouseMoved(ofMouseEventArgs& args);
        void mouseReleased(ofMouseEventArgs& args);
        void keyPressed(ofKeyEventArgs& args);
        void enable(bool b) {bEnabled = b;}
        void setResolution(int rx, int ry) {resx = rx; resy = ry;}

        ofParameterGroup parameters;

    protected:
        float resx, resy;
        float mouseX, mouseY;
        bool bToggle;
        bool bEnabled;

};
