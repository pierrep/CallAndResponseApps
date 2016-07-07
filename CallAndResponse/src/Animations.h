#pragma once

#include "ofMain.h"
#include "ofxPlaylist.h"

class BaseEffect;
class TreeData;

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
        BaseEffect* getEffect() {return effect[currentfx];}
//        void setEffect(int i);
//        void setEffect(const string name);
        void enableEffect(int i);
        void enableEffect(const string name);
        void nextEffect();
        void clearActiveEffects();
        void begin();
        void save();
        void load();

    protected:
        void testPattern();

        TreeData * data;

        /* Timing */
        int pattern;
        unsigned int pixelIndex;

        /* Animations */
        ofxPlaylist masterTimeline;
        ofFbo fxframe;
        vector<BaseEffect*> effect;
        vector<BaseEffect*> activeFx;
        int currentfx;

        ofPixels p;

        ofXml settings;
};

