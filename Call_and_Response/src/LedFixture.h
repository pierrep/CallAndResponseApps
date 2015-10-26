#pragma once
#include "ofMain.h"

#define NUM_PIXELS_PER_FIXTURE 8

class LedFixture : public ofNode
{
    public:
        LedFixture();
        ~LedFixture();
        void draw();
        void setMesh(ofMesh& mesh);
//        void setTransform(ofMatrix4x4& mat);
    protected:
        ofMesh mesh;
    private:
};
