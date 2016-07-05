#pragma once

#include "ofMain.h"
#include "ofxPlaylist.h"

class BaseEffect;
class TreeData;

class Animations
{

    public:
        Animations();
        ~Animations();

        void setup(TreeData * _data);
        void update(float curTime);
        void drawGui();
        void draw(float x, float y);
        void setPattern(int i);
        BaseEffect* getEffect() {return effect[currentfx];}
        void setEffect(int i);
        void enableEffect(int index);
        void nextEffect();
        void begin();
        void save();
        void load();

    protected:
        TreeData * data;

        /* Timing */
        int pattern;
        unsigned int pixelIndex;

        /* Animations */
        ofxPlaylist masterTimeline;
        ofFbo fxframe;
        vector<BaseEffect*> effect;
        int currentfx;

        ofPixels p;

        ofXml settings;
};

