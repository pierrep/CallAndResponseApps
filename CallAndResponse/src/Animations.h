#pragma once

#include "ofMain.h"
#include "ofxPlaylist.h"
#include "TreeData.h"

class BaseEffect;

enum EffectNames {FX_CALIBRATION = 0,FX_BLOOM,FX_LINE, FX_NOISEPARTICLE,FX_NOISE};

class Animations
{

    public:
        Animations();
        ~Animations();

        void setup(TreeData * _data);
        void update(float curTime);
        void drawGui();
        void draw(float x, float y);
        void updateFBO();
        void setPattern(int i);
        BaseEffect* getEffect() {return effect[currentFx];}
        void enableEffect(int i);
        void enableEffect(const string name);
        void nextEffect();
        void clearActiveEffects();
        void updateActiveEffectPos(ofVec2f);
        void begin();
        void save();
        void load();

    protected:
        void testPattern();

        TreeData * data;

        /* Test patterns */
        int pattern;
        unsigned int pixelIndex;

        /* Animations */
        ofxPlaylist masterTimeline;
        ofFbo fxframe;
        vector<BaseEffect*> effect;
        vector<BaseEffect*> activeFx;
        unsigned int currentFx;

        /* PBO optimisation */
		bool bUsePBO;
		bool bReadyToSend;
        #if !defined(TARGET_RASPBERRY_PI)
        ofBufferObject pixelBufferBack, pixelBufferFront;
		#endif

        ofPixels framePixels;

        ofXml settings;
};

