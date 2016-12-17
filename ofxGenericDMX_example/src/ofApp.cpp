#include <stdlib.h>
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetFrameRate( 44 );

	//zero our DMX value array
	memset( dmxData_, 0, DMX_DATA_LENGTH );

	//open the device
	dmxInterface_ = ofxGenericDmx::openFirstDevice();
	if ( dmxInterface_ == 0 ) printf( "No Enttec Device Found\n" );
	else printf( "isOpen: %i\n", dmxInterface_->isOpen() );

	//example/color-related-stuff
	generateColorPicker(ofGetWidth(), ofGetHeight());
	red=green=blue=0;
	demoMode = 0;

	frames = 0;

	printf("ofxGenericDmx addon version: %s.%s\n", ofxGenericDmx::VERSION_MAJOR, ofxGenericDmx::VERSION_MINOR);

    lightID = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

	/*
	 *	let's set some dmx values to be communicated with your dmx interface!
	 *
	 *	obviously this is based on the way you've set up your dmx network and devices.
	 *	namely the addressing (which light/device is set to which channel)
	 *	and the number of channels each device uses.
	 *
	 *	most lights for example use 3 channels for R,G & B values and oftentimes
	 *	also a fourth 'master' channel that's used to set the overall brightness.
	 *
	 *	this example is based on a dmx light thas uses 3 dmx channels (R,G & B)
	 *	the light's address is set to channel 10 (so R is channel 10, G = 11 & B = 12).
	 *
	 *  change this to match your own setup!
	 */

	//put some color in this example:
	setColorsToSend();

	//asign our colors to the right dmx channels
    /* AUDIO TEST
    dmxData_[510] = int(red);
    dmxData_[511] = 2;//int(green);
	dmxData_[3] = int(blue);
    */

    //dmxData_[],0
    memset(dmxData_,0,512);

    dmxData_[1+(24*lightID)] = int(red);
    dmxData_[2+(24*lightID)] = int(green);
    dmxData_[3+(24*lightID)] = int(blue);
    dmxData_[4+(24*lightID)] = int(red);
    dmxData_[5+(24*lightID)] = int(green);
    dmxData_[6+(24*lightID)] = int(blue);
    dmxData_[7+(24*lightID)] = int(red);
    dmxData_[8+(24*lightID)] = int(green);
    dmxData_[9+(24*lightID)] = int(blue);
    dmxData_[10+(24*lightID)] = int(red);
    dmxData_[11+(24*lightID)] = int(green);
    dmxData_[12+(24*lightID)] = int(blue);
    dmxData_[13+(24*lightID)] = int(red);
    dmxData_[14+(24*lightID)] = int(green);
    dmxData_[15+(24*lightID)] = int(blue);
    dmxData_[16+(24*lightID)] = int(red);
    dmxData_[17+(24*lightID)] = int(green);
    dmxData_[18+(24*lightID)] = int(blue);
    dmxData_[19+(24*lightID)] = int(red);
    dmxData_[20+(24*lightID)] = int(green);
    dmxData_[21+(24*lightID)] = int(blue);
    dmxData_[22+(24*lightID)] = int(red);
    dmxData_[23+(24*lightID)] = int(green);
    dmxData_[24+(24*lightID)] = int(blue);
	//force first byte to zero (it is not a channel but DMX type info - start code)
	dmxData_[0] = 0;

	if ( ! dmxInterface_ || ! dmxInterface_->isOpen() ) {
		printf( "Not updating, enttec device is not open.\n");
	}
	else{
		//send the data to the dmx interface
		dmxInterface_->writeDmx( dmxData_, DMX_DATA_LENGTH );
	}
}

//--------------------------------------------------------------
void ofApp::setColorsToSend(){

	/*
	 *	three different examples/demoModes that set/generate a color
	 *	the colorPicker is actually quite usefull!
	 */

	switch (demoMode) {
		case 0:
		//use the colorPicker
			pickColor(mouseX, mouseY);
			break;
		case 1:
		//static green!
			red		= 255;
			green	= 255;
			blue	= 0;
			break;
		case 2:
		//something a bit more dynamic
			frames = ++frames % 360;
			//static const float DegRadFactor = PI / 180.0f;
			float radR = ofDegToRad(frames);
			float radG = ofDegToRad(frames + 120);
			float radB = ofDegToRad(frames + 240);
			float intensity = 255;
			red		= ( cosf( radR ) + 1.0f ) * intensity / 2;
			green	= ( sinf( radG ) + 1.0f ) * intensity / 2;
			blue	= ( sinf( radB ) + 1.0f ) * intensity / 2;
			break;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	//use the color for the app background
	ofBackground(red, green, blue);
	ofSetColor(255, 255, 255);

	//app info
	switch (demoMode) {
		case 0:
		//colorPicker
			colorPicker.draw(0,0);
			ofDrawBitmapString("Color Picker", 10, 20);
            ofDrawBitmapString("Colour: "+ofToString(red)+" "+ofToString(green)+" "+ofToString(blue),ofGetWidth()-160,20);
			break;
		case 1:
		//static green
			ofDrawBitmapString("Static Green", 10, 20);
			break;
		case 2:
		//dynamic
			ofDrawBitmapString("Dynamic Color", 10, 20);
			break;
	}

	ofDrawBitmapString("use arrow LEFT & RIGHT keys to change modes", 70, 500);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key) {
		case OF_KEY_RIGHT:
			demoMode++;
			if(demoMode>2)demoMode=0;
			break;
		case OF_KEY_LEFT:
			demoMode--;
			if(demoMode<0)demoMode=2;
			break;
        case 'n':
            lightID++;
            if(lightID > 10) lightID = 0;
            break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::exit(){

	if ( dmxInterface_ && dmxInterface_->isOpen() ) {
		// send all zeros (black) to every dmx channel and close!
		for ( int i = 0; i <= DMX_DATA_LENGTH; i++ ) dmxData_[i] = 0;
		dmxInterface_->writeDmx( dmxData_, DMX_DATA_LENGTH );
		dmxInterface_->close();
	}
}

//--------------------------------------------------------------
void ofApp::generateColorPicker(int width , int height){

	//generate a colorPicker image (needs oF007 for the color operations)

	//this function will create a Radial Spectrum Color Chart
	//inspired by Mykhel Trinitaria:
	//http://mtrinitaria.com/mykhel/color-spectrum-chart-as3/
	//done in just a few lines of code by Rick Companje

	float w = width;
    float h = height;
    float cx = w/2;
    float cy = h/2;

    colorPicker.allocate(w,h,OF_IMAGE_COLOR);

    for (float y=0; y<h; y++) {
        for (float x=0; x<w; x++) {

            float angle = atan2(y-cy,x-cy)+PI;
            float dist = ofDist(x,y,cx,cy);
            float hue = angle/TWO_PI*255;
            float sat = ofMap(dist,0,w/4,0,255,true);
            float bri = ofMap(dist,w/4,w/2,255,0,true);

            colorPicker.setColor(x,y,ofColor::fromHsb(hue,sat,bri));
        }
    }
    colorPicker.update();
}

//--------------------------------------------------------------
void ofApp::pickColor(int x , int y){

	/*
	//get the color value in our colorPicker image under the mouse location
	int bpp = colorPicker.bpp /8;	//from bits per pixel to bytes per pixel
	//set our colors:
	red = colorPicker.getPixels()[ (y*512+x)*bpp ];
	green = colorPicker.getPixels()[ (y*512+x)*bpp +1 ];
	blue = colorPicker.getPixels()[ (y*512+x) *bpp +2 ];
	*/

	//get the color value in our colorPicker image under the mouse location
	red = colorPicker.getColor(x, y).r;
	green = colorPicker.getColor(x, y).g;
	blue = colorPicker.getColor(x, y).b;
}
