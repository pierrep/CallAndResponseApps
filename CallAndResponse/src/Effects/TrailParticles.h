#pragma once

#include "ofMain.h"
#include "BaseEffect.h"

#define NUM_BILLBOARDS 6000

class TrailParticles : public BaseEffect
{
    public:

        TrailParticles();
        ~TrailParticles();

        void update(float time);
        void draw(float x, float y, float w, float h);
        void setup();
        void begin();

		ofShader billboardShader;
		ofVboMesh billboards;
		ofVec3f billboardVels[NUM_BILLBOARDS];

        ofParameter<float> duration;
        ofParameter<float> speed;

    private:
        float curTime, prevTime;
        bool bPlayAnim;
        int currentTree;
		int startPos;
};
