#include "ModelLoader.h"
#include "LedFixture.h"
#include "TreeMesh.h"

ModelLoader::ModelLoader()
{
    //ctor
}

ModelLoader::~ModelLoader()
{
    //dtor
}

void ModelLoader::load(vector<TreeMesh>& trees, vector<LedFixture>& lights, vector<LedPixel>& pixels)
{
    model.loadModel("E2-skeleton.obj", false);
    //model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75 , 0);
    vector<string> names;
    names = model.getMeshNames();

    model.update();
    //mesh = model.getMesh(0);
    //mesh = model.getMesh("Tree_Num1");



}
