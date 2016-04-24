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

};
