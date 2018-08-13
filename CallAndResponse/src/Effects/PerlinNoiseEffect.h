#pragma once

#include "ofMain.h"
#include "BaseEffect.h"

class PerlinNoiseEffect : public BaseEffect
{
    public:

        PerlinNoiseEffect();
        ~PerlinNoiseEffect();

        void update(float time);
        void draw(float x, float y, float w, float h);
        void setup();
        void begin();
        void onKeyframe(ofxPlaylistEventArgs& args);

        ofShader shader;
        ofFloatColor colour;
        bool bReady;
        float alpha;

};
