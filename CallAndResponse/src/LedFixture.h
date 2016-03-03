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
        void update();

        void setMesh(ofMesh& mesh);        
        void setId(int _id) {id = _id;}
        void setColour(ofColor c);
        void setBrightness(float val);
        void setPosition(ofVec2f _pos) {pos = _pos;}

        const int getId() {return id;}
        const ofVec2f getPosition() {return pos;}

        void setupPixels();

        void fadeOn();
        vector<LedPixel* > pixels;

    protected:
        ofMesh mesh;
        int id;
        ofVec2f pos;

    private:
};
