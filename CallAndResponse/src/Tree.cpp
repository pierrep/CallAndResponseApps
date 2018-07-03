#include "Tree.h"

Tree::Tree()
{
	clearBufferPixels();
    bPlayPing = false;
    pingcount = 0;
    volume = 1;
    bIsDirty = false;
}

//--------------------------------------------------------------
Tree::~Tree()
{
    //dtor
}

//--------------------------------------------------------------
void Tree::clear()
{
	clearBufferPixels();
    for(int i = 0; i < lights.size();i++)
    {
        lights[i]->clear();
    }
}

//--------------------------------------------------------------
void Tree::doFade()
{
    for(unsigned int i=0; i < lights.size();i++)
    {
        for(unsigned int j=0; j < lights[i]->pixels.size();j++) {
            lights[i]->pixels[j]->fadeOff(ofRandom(1000,8000));
        }
    }
}

//--------------------------------------------------------------
void Tree::doPixelFade()
{
    for(unsigned int i=0; i < lights.size();i++)
    {
        for(unsigned int j=0; j < lights[i]->pixels.size();j++) {
            lights[i]->pixels[j]->turnOff(ofRandom(100,1500));
        }
    }
}

//--------------------------------------------------------------
void Tree::update()
{
    bool val = false;
    unsigned int count = 0;

    for(unsigned int i=0; i < lights.size();i++)
    {
        val = lights[i]->update();
        if(val) {
            bIsDirty = true;
        }
        else {
            count++;
        }
    }
    if (count >= lights.size()) bIsDirty = false;

    updatePing();

    updateBufferPixels();
}

//--------------------------------------------------------------
void Tree::draw(int x, int y)
{
    const int pixsize = 4;
    int idx = 0;

    ofPushStyle();
    for(unsigned int i=0; i < lights.size();i++)
    {
        for(unsigned int j=0; j < lights[i]->pixels.size();j++) {
            ofSetColor((int) buf[idx], (int) buf[idx+1], (int) buf[idx+2]);
            ofDrawRectangle(10 + x+i*pixsize,y+j*pixsize,pixsize,pixsize);
            idx+=3;
        }
        if(bIsDirty) {
            ofSetColor(255,0,0);
            ofDrawRectangle(10 + x -pixsize,y,pixsize,pixsize*8);
        }
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void Tree::updateBufferPixels()
{
    int bufindex = 0;
    for(int i=0; i < lights.size();i++)
    {
        for(int j=0; j < lights[i]->pixels.size();j++) {
            for(int k = 0; k < 3; k++) {
                buf[bufindex] = lights[i]->pixels[j]->getDMXValue(k);
                bufindex++;
            }
        }
    }
}

//--------------------------------------------------------------
void Tree::clearBufferPixels()
{
	memset(buf, 0, 512 * sizeof(unsigned char));
}

//--------------------------------------------------------------
void Tree::updatePing()
{
//    /* set per tree volume */
//    buf[500] = volume;

    /* check if we should play the ping */
    if(bPlayPing) {

        buf[499] = volume;
        pingcount++;
        if(pingcount >= 2) {
            pingcount = 0;
            bPlayPing = false;
        }
    } else {
        buf[499] = 0;
    }
}

//--------------------------------------------------------------
void Tree::playPing()
{
    bPlayPing = true;
}
