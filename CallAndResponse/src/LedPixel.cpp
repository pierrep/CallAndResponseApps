#include "LedPixel.h"

using namespace Playlist;

LedPixel::LedPixel()
{
    id = 0;
    pos = ofVec2f::zero();
    pos3D = ofVec3f::zero();
    col = ofColor::black;
    brightness = 1.0f;
    bIsDirty = false;

}

//--------------------------------------------------------------
LedPixel::~LedPixel()
{
    //dtor
}

//--------------------------------------------------------------
void LedPixel::fadeOn(int i)
{
    brightness = 0.0f;
    col.r = 1.0f;
    playlist.addKeyFrame(Action::pause(i*100.0f));
    playlist.addKeyFrame(Action::tween(200.f, &brightness, 1.0f,TWEEN_QUAD,TWEEN_EASE_IN));
    playlist.addToKeyFrame(Action::tween(200.0f,200.f,&brightness, 0.0f, TWEEN_QUAD, TWEEN_EASE_OUT));
    bIsDirty = true;
}

//--------------------------------------------------------------
void LedPixel::setPosition(ofVec2f& _pos)
{
    pos = _pos;
}

//--------------------------------------------------------------
void LedPixel::set3DPosition(ofVec3f& _pos)
{
    pos3D = _pos;
}

//--------------------------------------------------------------
void LedPixel::setBrightness(float value)
{
    brightness = value;
    bIsDirty = true;
}

//--------------------------------------------------------------
void LedPixel::update()
{
    playlist.update();
}

//--------------------------------------------------------------
unsigned char LedPixel::getDMXValue(int idx)
{
    if((idx >=0) && (idx < 3)) {
        float tmpval = brightness * (float) col[idx] * 255.0f;
        tmpval = ofClamp(tmpval,0,255.0f);
        unsigned char val = (int) tmpval;
        return val;
    }
    return 0;
}
