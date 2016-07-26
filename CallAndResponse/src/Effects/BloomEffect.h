#pragma once

#include "ofMain.h"
#include "BaseEffect.h"

class BloomEffect : public BaseEffect
{
    public:

        BloomEffect();
        ~BloomEffect();

        void update(float time);
        void draw();
        void draw(float x, float y, float w, float h);
        void setup();
        void begin();

        ofParameter<int> maxradius;
        ofParameter<float> bloomspeed;
        float radius;
        float ratio;
        ofColor c1,c2;

        unsigned int pixelIndex;
};
