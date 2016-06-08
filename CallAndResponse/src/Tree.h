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
        void setId(int _id) {id = _id;}
        const int getId() {return id;}
        void setName(string _name) {name = _name;}
        void setMapPos(ofVec2f _pos) {pos = _pos;}
        const ofVec2f getMapPos() { return pos;}
        const string getName() {return name;}
        const unsigned char*  getBuffer() {return &buf[0];}
        void clear();
        bool isDirty() {return (bIsDirty?true:false);}
        void playPing();

        vector<LedFixture *> lights;


    protected:
        int id;
        string name;
        ofNode node;
        ofMesh mesh;
        unsigned char buf[512];
        ofVec2f pos;
        bool    bIsDirty;

    private:
};
