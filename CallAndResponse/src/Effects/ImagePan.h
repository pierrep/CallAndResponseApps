#pragma once

#include "ofMain.h"
#include "BaseEffect.h"

class ImagePan : public BaseEffect
{
    public:

        ImagePan();
        ~ImagePan();

        void update(float time);
        void draw(float x, float y, float w, float h);
        void setup();
        void begin();
        void onKeyframe(ofxPlaylistEventArgs& args);
        void keyPressed(ofKeyEventArgs& args);

        //ofImage image[13];

        //ofParameter<string> imagename;
        ofParameter<float> pan_speed;
        float height;
        bool bEndSequence;
        bool bDoRotate;
        size_t currentTree;
        float angle;
        float adder;
        int numImgs;
        bool bFlip;
};
