#pragma once
#include "ofMain.h"
#include "LedFixture.h"

class Tree
{
    public:
        Tree();
        ~Tree();
        void draw();
        void setMesh(ofMesh& mesh);
        void setTransform(ofMatrix4x4& mat);

    protected:
        ofNode node;
        ofMesh mesh;
        vector<LedFixture> lights;

    private:
};
