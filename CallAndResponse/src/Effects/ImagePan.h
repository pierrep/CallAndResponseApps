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

        ofImage image[6];

        //ofParameter<string> imagename;
        ofParameter<float> pan_speed;
        float height;
        bool bEndSequence;
        bool bDoRotate;
        int currentTree;
        int currentImage;
        float angle;
        float adder;
};
