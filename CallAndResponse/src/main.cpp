#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

    ofSetLogLevel(OF_LOG_NOTICE);

    #if defined(TARGET_RASPBERRY_PI)
    /*
		 ofGLESWindowSettings settings;
		// settings.setGLESVersion(2);
		 settings.width = 320;
		 settings.height = 240;
		 settings.windowMode = OF_WINDOW;
		 ofCreateWindow(settings);
	*/
        ofSetupOpenGL(200,200,OF_WINDOW);
    #else
        ofSetupOpenGL(1600,900,OF_WINDOW);
    #endif

    ofRunApp(new ofApp());

}
