#pragma once

#include "ofMain.h"
#include "BaseEffect.h"

class NoiseEffect : public BaseEffect
{
    public:

        NoiseEffect();
        ~NoiseEffect();

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


        ofImage noiseImage;
        int noiseStartX;
        int noiseStartY;
};
