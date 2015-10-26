#pragma once
#include "ofMain.h"

#define DISTANCE_BETWEEN_PIXELS 0.05

class LedPixel
{
    public:
        LedPixel();
        ~LedPixel();
        void setPosition(ofVec3f& _pos);

    protected:

        ofVec3f pos;
        ofColor colour;
        float   brightness;
    private:
};
