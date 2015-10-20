#pragma once
#include "ofMain.h"

class TreeMesh
{
    public:
        TreeMesh();
        ~TreeMesh();
        void drawMesh();
        void setMesh(ofMesh& mesh);

    protected:
        ofMesh mesh;

    private:
};
