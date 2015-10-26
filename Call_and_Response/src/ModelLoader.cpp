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

    const aiScene* scene = model.getAssimpScene();
    for(unsigned int i=0; i < scene->mRootNode->mNumChildren; i++) {
        string name = scene->mRootNode->mChildren[i]->mName.data;
        if(name.compare(0,4,"Tree") == 0) {
            TreeMesh treeMesh;
            ofMesh _mesh = model.getMesh(name);
            treeMesh.setMesh(_mesh);

            aiMatrix4x4 m = scene->mRootNode->mChildren[i]->mTransformation;
            m.Transpose();
            ofMatrix4x4 matrix(m.a1, m.a2, m.a3, m.a4,
                        m.b1, m.b2, m.b3, m.b4,
                        m.c1, m.c2, m.c3, m.c4,
                        m.d1, m.d2, m.d3, m.d4);

            treeMesh.setTransform(matrix);
            trees.push_back(treeMesh);
        }
        else if(name.compare(0,5,"Light") == 0) {
            LedFixture led;
            ofMesh _mesh = model.getMesh(name);
            led.setMesh(_mesh);

            aiMatrix4x4 m = scene->mRootNode->mChildren[i]->mTransformation;
            m.Transpose();
            ofMatrix4x4 matrix(m.a1, m.a2, m.a3, m.a4,
                        m.b1, m.b2, m.b3, m.b4,
                        m.c1, m.c2, m.c3, m.c4,
                        m.d1, m.d2, m.d3, m.d4);

            led.setTransformMatrix(matrix);
            lights.push_back(led);

            for(int i=-NUM_PIXELS_PER_FIXTURE/2; i < NUM_PIXELS_PER_FIXTURE/2; i++) {
                LedPixel p;
                ofVec3f c = _mesh.getCentroid();
                c.y += (i * DISTANCE_BETWEEN_PIXELS);
                p.setPosition(c);
                pixels.push_back(p);
            }
        }

    }


}
