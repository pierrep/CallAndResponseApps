#pragma once

#include "ofMain.h"
#include "BaseEffect.h"

class EmptyEffect : public BaseEffect
{
    public:

        EmptyEffect();
        ~EmptyEffect();

        void update(float time);
        void draw();
        void draw(float x, float y, float w, float h);
        void setup();

};
