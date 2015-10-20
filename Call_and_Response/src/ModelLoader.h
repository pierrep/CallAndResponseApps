#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

#include "TreeMesh.h"
#include "LedFixture.h"
#include "LedPixel.h"

class ModelLoader
{
    public:
        ModelLoader();
        ~ModelLoader();

        void load(vector<TreeMesh>& trees, vector<LedFixture>& lights, vector<LedPixel>& pixels);

    protected:

        ofxAssimpModelLoader model;

    private:
};
