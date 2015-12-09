#pragma once
#include "ofMain.h"
#include "LedFixture.h"

class Tree
{
    public:
        Tree();
        ~Tree();
        void draw();
        void update();
        void setMesh(ofMesh& mesh);
        void setTransform(ofMatrix4x4& mat);
        void setId(int _id) {id = _id;};
        void setName(string _name) {name = _name;};
        const unsigned char*  getBuffer() {return &buf[0];};
        vector<LedFixture> lights;


    protected:
        int id;
        string name;
        ofNode node;
        ofMesh mesh;
        unsigned char buf[512];

    private:
};
