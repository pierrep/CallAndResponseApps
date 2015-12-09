#pragma once

#include "ofMain.h"
#include "ModelLoader.h"
#include "ofxGameCamera.h"
#include "ofxXmlSettings.h"
#include "ofxArtnet.h"


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

        void loadTreeData(vector<Tree>& trees);
        //void loadTreeData(vector<Tree>& trees, vector<LedFixture>& lights, vector<LedPixel>& pixels);
		void drawModel();


        ModelLoader  loader;
        vector<Tree> trees;
        //vector<LedFixture> lights;
        //vector<LedPixel> pixels;

        ofLight	light;
        //ofEasyCam cam;
        ofxGameCamera cam;

        ofxXmlSettings xml;

        ofxArtnet artnet;
};
