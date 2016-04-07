#pragma once

#include "ofMain.h"
#include "TreeData.h"
#include "Effects/BaseEffect.h"

class Animations
{

    public:
        Animations();

        void setup(TreeData * _data);
        void update();
        void draw(float x, float y);
        void setTestPattern(int i);
        BaseEffect* getEffect() {return effect[currentfx];}

    protected:
        TreeData * data;

        /* Timing */
        float curTime, prevTime;
        int testPattern;
        unsigned int pixelIndex;

        ofFbo fxframe;
        vector<BaseEffect*> effect;
        int currentfx;

        ofPixels p;
};

