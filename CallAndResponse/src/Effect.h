#pragma once

#include "ofMain.h"
#include "BaseEffect.h"

class Effect : public BaseEffect
{
    public:

        Effect();
        ~Effect();

        void update();
        void draw();
        void draw(float x, float y, float w, float h);
        void setup();
        void threshold(bool _upload);

        ofParameter<int> resolution;
        ofParameter<float> noiseFrequency;
        ofParameter<bool> animate;

        ofParameter<bool> doThreshold;
        ofParameter<int> thresholdLow;
        ofParameter<int> thresholdHigh;
        ofParameter<bool> invert;

        int noiseStartX;
        int noiseStartY;
};
