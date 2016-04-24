#pragma once

#include "ofMain.h"
#include "TreeData.h"
#include "ofxPlaylist.h"
#include "Effects/BaseEffect.h"

class Animations
{

    public:
        Animations();

        void setup(TreeData * _data);
        void update();
        void drawGui();
        void draw(float x, float y);
        void setTestPattern(int i);
        BaseEffect* getEffect() {return effect[currentfx];}
        void nextEffect();
        void begin();
        void save();
        void load();

    protected:
        TreeData * data;

        /* Timing */
        float curTime, prevTime;
        int testPattern;
        unsigned int pixelIndex;

        /* Animations */
        ofxPlaylist masterTimeline;
        ofFbo fxframe;
        vector<BaseEffect*> effect;
        int currentfx;

        ofPixels p;

        ofXml settings;
};

