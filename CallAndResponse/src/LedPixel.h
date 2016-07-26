#pragma once
#include "ofMain.h"
#include "ofxPlaylist.h"


class LedPixel
{
    public:
        LedPixel();
        ~LedPixel();

        void clear();
        void setPosition(ofVec2f& _pos);
        void set3DPosition(ofVec3f& _pos);
        unsigned char getDMXValue(int idx);
        void setBrightness(float value);
        void setColour(ofColor c);
        void setId(int _id) {id = _id;}

        const ofVec2f getPosition() {return pos;}
        const float getBrightness() {return brightness;}
        const ofColor getColour() {return col;}
        const int getId() {return id;}

        void fadeOn(float time);
        void fadeOff(float time);
        bool update();
        bool isDirty() {return bIsDirty;}
        ofxPlaylist playlist;


    protected:
        int id;
        ofVec2f pos;
        ofVec3f pos3D;
        ofFloatColor col;
        float   brightness;
        unsigned char dmx[3];
        bool    bIsDirty;

    private:
};
