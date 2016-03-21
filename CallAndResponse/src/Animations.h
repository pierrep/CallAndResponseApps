#pragma once

#include "ofMain.h"
#include "TreeData.h"

class Animations
{

    public:
        Animations();

        void setup(TreeData * _data);
        void update();
        void setTestPattern(int i);

    protected:
        TreeData * data;

        /* Timing */
        float curTime, prevTime;
        int testPattern;
        int pixelIndex;
};

