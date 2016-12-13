#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

    ofSetLogLevel(OF_LOG_VERBOSE);

    #if defined(TARGET_RASPBERRY_PI)
        ofSetupOpenGL(400,300,OF_WINDOW);
    #else
        ofSetupOpenGL(1600,900,OF_WINDOW);
    #endif

    ofRunApp(new ofApp());

}
