#pragma once

#include "ofMain.h"
#include "ofxGameCamera.h"
#include "ofxXmlSettings.h"
#include "ofxArtnet.h"
#include "ofxGui.h"
#include "Tree.h"
#include "LightsEditor.h"
#include "TreeData.h"

class ofApp : public ofBaseApp{

    public:
            void setup();
            void update();
            void draw();
            void exit();
            void keyPressed(int key);
            void keyReleased(int key);
            void mouseMoved(int x, int y );
            void mouseDragged(int x, int y, int button);
            void mousePressed(int x, int y, int button);
            void mouseReleased(int x, int y, int button);
            void mouseEntered(int x, int y);
            void mouseExited(int x, int y);
            void windowResized(int w, int h);
            void dragEvent(ofDragInfo dragInfo);
            void gotMessage(ofMessage msg);

            void clearTrees();
            void drawModel();


        /* Trees */
        LightsEditor editor;
        TreeData treedata;
        vector<Tree *> trees;
        int currentTree;

        /* 3D settings */
        ofLight	light;
        //ofEasyCam cam;
        ofxGameCamera cam;

        /* ArtNet */
        ofxArtnet artnet;

        /* Timing */
        float curTime, prevTime;
        float curTimeTree, prevTimeTree;
        int testPattern;
        int lightIndex;
        int pixelIndex;
        float wait_time;

        /* GUI */
        ofParameter<float> brightness;
        ofParameter<ofColor> colour;
        ofParameterGroup parameters;
        ofxPanel gui;
};
