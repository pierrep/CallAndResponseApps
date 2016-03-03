#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "Tree.h"

class TreeData
{
    public:
        TreeData();
        ~TreeData();
        void load(vector<Tree *>& trees);
        void save(vector<Tree *>& trees);

    protected:

        ofxXmlSettings xml;

    private:
};
