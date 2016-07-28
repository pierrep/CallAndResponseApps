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
    playlist.clear();
}

//--------------------------------------------------------------
void LedPixel::clear()
{
    setBrightness(0.0f);
    setColour(ofColor::black);
    playlist.clear();
    bIsDirty = false;
}

//--------------------------------------------------------------
void LedPixel::setColour(ofColor c)
{
    col = c;
    bIsDirty = true;
}

//--------------------------------------------------------------
void LedPixel::fadeOn(float time)
{
    brightness = 0.0f;
    playlist.addKeyFrame(Action::tween(time, &brightness, 1.0f,TWEEN_QUAD,TWEEN_EASE_IN));
    bIsDirty = true;
}

//--------------------------------------------------------------
void LedPixel::fadeOff(float time)
{
    playlist.addKeyFrame(Action::tween(2000.0f,time, &brightness, 0.0f,TWEEN_QUAD,TWEEN_EASE_IN));

}

//--------------------------------------------------------------
void LedPixel::turnOff(float time)
{
    playlist.addKeyFrame(Action::pause(time));
    playlist.addKeyFrame(Action::tween(1.0f, &brightness, 0.0f,TWEEN_QUAD,TWEEN_EASE_IN));

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
bool LedPixel::update()
{
    playlist.update();

    if((brightness <= 0.0f) || (col == ofColor::black))
    {
        bIsDirty = false;
    }

    return bIsDirty;
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
