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
        const int getId() {return id;};
        void setId(int _id) {id = _id;};
        void setupPixels();
//        void setTransform(ofMatrix4x4& mat);
        vector<LedPixel> pixels;

    protected:
        ofMesh mesh;
        int id;

    private:
};
