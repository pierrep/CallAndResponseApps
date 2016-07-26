#pragma once
#include "ofMain.h"
#include "LedPixel.h"

#define NUM_PIXELS_PER_FIXTURE 8

class LedFixture : public ofNode
{
    public:
        LedFixture();
        ~LedFixture();
        void draw();
        bool update();

        void clear();
        void setId(int _id) {id = _id;}
        void setColour(ofColor c);
        void setBrightness(float val);
        void setPosition(ofVec2f _pos);

        const int getId() {return id;}
        const ofVec2f getPosition() {return pos;}

        void setupPixels(ofVec2f pos, float pixelWidth);

        void fadeOn(float time);
        vector<LedPixel* > pixels;

    protected:
        int id;
        ofVec2f pos;
        bool    bIsDirty;
        float   pixelWidth;

    private:
};
