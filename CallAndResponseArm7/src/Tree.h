#pragma once
#include "ofMain.h"

class LedFixture;

class Tree
{
    public:
        Tree();
        ~Tree();
        void draw(int x, int y);
        void update();
        void setId(int _id) {id = _id;}
        const int getId() {return id;} // id = universe
        void setVolume(int _vol) {volume = _vol;}
        const int getVolume() {return volume;}
        void setName(string _name) {name = _name;}
        void setMapPos(ofVec2f _pos) {pos = _pos;}
        const ofVec2f getMapPos() { return pos;}
        const string getName() {return name;}
        void updateBufferPixels();
        const unsigned char*  getBufferPixels() {return &buf[0];}
        void clear();
        bool isDirty() {return (bIsDirty?true:false);}
        void updatePing();
        void playPing();

        vector<LedFixture *> lights;


    protected:
        int id;
        string name;
        unsigned char buf[512];
        ofVec2f pos;
        bool    bIsDirty;
        bool    bPlayPing;
        int     pingcount;
        int     volume;

    private:
};
