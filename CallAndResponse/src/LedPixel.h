#pragma once
#include "ofMain.h"
#include "ofxPlaylist.h"

#define DISTANCE_BETWEEN_PIXELS 0.05

class LedPixel
{
    public:
        LedPixel();
        ~LedPixel();
        //LedPixel(const LedPixel&);
        void setPosition(ofVec2f& _pos);
        void set3DPosition(ofVec3f& _pos);
        unsigned char getDMXValue(int idx);
        void setBrightness(float value);
        void setColour(ofColor c) {col = c;}
        void setId(int _id) {id = _id;}
        const float getBrightness() {return brightness;}
        void fadeOn(int i);
        void update();
        ofxPlaylist playlist;


    protected:
        int id;
        ofVec2f pos;
        ofVec3f pos3D;
        ofFloatColor col;
        float   brightness;
        unsigned char dmx[3];

    private:
};
