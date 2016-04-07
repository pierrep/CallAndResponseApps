#pragma once

#include "ofMain.h"
#include "BaseEffect.h"

class BloomEffect : public BaseEffect
{
    public:

        BloomEffect();
        ~BloomEffect();

        void update();
        void draw();
        void draw(float x, float y, float w, float h);
        void setup();
        void threshold(bool _upload);

        //~ ofParameter<int> resolution;
        //~ ofParameter<float> noiseFrequency;

};
