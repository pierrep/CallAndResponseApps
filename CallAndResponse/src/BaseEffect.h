
#pragma once
#include "ofMain.h"

class BaseEffect
{
    public:

        BaseEffect() {};
        virtual ~BaseEffect() {};

        virtual void setup() = 0;
        virtual void draw() = 0;
        virtual void draw(float x, float y, float w, float h) = 0;
        virtual void update() = 0;
        void setResolution(int rx, int ry) {resx = rx; resy = ry;}


        ofImage noiseImage;

    protected:
        float resx, resy;

};
