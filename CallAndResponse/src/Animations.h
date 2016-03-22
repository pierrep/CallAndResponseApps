#pragma once

#include "ofMain.h"
#include "TreeData.h"
#include "BaseEffect.h"

class Animations
{

    public:
        Animations();

        void setup(TreeData * _data);
        void update();
        void draw(float x, float y);
        void setTestPattern(int i);

    protected:
        TreeData * data;

        /* Timing */
        float curTime, prevTime;
        int testPattern;
        unsigned int pixelIndex;

        ofFbo fxframe;
        BaseEffect* effect;
};

