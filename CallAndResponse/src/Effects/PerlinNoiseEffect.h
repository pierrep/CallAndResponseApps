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

        ofShader shader;
/*        ofParameter<int> resolution;
        ofParameter<float> noiseFrequency;
        ofParameter<bool> animate;

        ofParameter<bool> doThreshold;
        ofParameter<int> thresholdLow;
        ofParameter<int> thresholdHigh;
        ofParameter<bool> invert;
*/


};
