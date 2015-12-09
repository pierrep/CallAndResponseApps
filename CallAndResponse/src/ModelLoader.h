#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

#include "Tree.h"
#include "LedFixture.h"
#include "LedPixel.h"

class ModelLoader
{
    public:
        ModelLoader();
        ~ModelLoader();

        void load(vector<Tree>& trees);

    protected:

        ofxAssimpModelLoader model;
        ofMesh mesh;

    private:
};