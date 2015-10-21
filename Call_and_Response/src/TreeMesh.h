#pragma once
#include "ofMain.h"

class TreeMesh
{
    public:
        TreeMesh();
        ~TreeMesh();
        void draw();
        void setMesh(ofMesh& mesh);
        void setTransform(ofMatrix4x4& mat);

    protected:
        ofNode node;
        ofMesh mesh;

    private:
};
