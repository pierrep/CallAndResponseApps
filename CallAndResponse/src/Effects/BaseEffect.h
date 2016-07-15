#pragma once

#include "ofMain.h"

#if !defined(TARGET_RASPBERRY_PI)
#define USE_GUI 1
#endif

#ifdef USE_GUI
#include "ofxDatGui.h"
#endif

#include "ofxPlaylist.h"

using namespace Playlist;

class BaseEffect
{
    public:

        BaseEffect();
        virtual ~BaseEffect();

        virtual void setup() = 0;
        virtual void drawGui();
        virtual void draw(float x, float y, float w, float h) = 0;
        virtual void update(float time);
        virtual void begin() = 0;
        void setupGui();
        void enableEditing();
        void disableEditing();
        void mousePressed(ofMouseEventArgs& args);
        void mouseDragged(ofMouseEventArgs& args);
        void mouseMoved(ofMouseEventArgs& args);
        void mouseReleased(ofMouseEventArgs& args);
        void keyPressed(ofKeyEventArgs& args);
        void enable(bool b) {bEnabled = b;}
        const string getName();
        void setResolution(int rx, int ry) {resx = rx; resy = ry;}
        void updateMouse(ofVec2f pos) {mouseX = pos.x; mouseY = pos.y;}

        float effectHeight, effectWidth;

        ofParameterGroup parameters;

    protected:
        float resx, resy;
        float mouseX, mouseY;
        bool bToggle;
        ofParameter<bool> bEnabled;
        string baseName;
        string name;
#ifdef USE_GUI
        ofxDatGuiFolder* paramfolder;
#endif
        ofxPlaylist timeline;

};
