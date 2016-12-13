#pragma once

#include "ofMain.h"
#include "BaseEffect.h"

class CalibrateEffect : public BaseEffect
{
    public:

        CalibrateEffect();
        ~CalibrateEffect();

        void update(float time);
        void draw();
        void draw(float x, float y, float w, float h);
        void setup();
        void begin();

        ofParameter<bool> orientation;

};
