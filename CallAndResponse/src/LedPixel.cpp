#include "LedPixel.h"

LedPixel::LedPixel()
{
    col = ofColor::black;
    col = ofColor::red;
    brightness = 1.0f;
}

LedPixel::~LedPixel()
{
    //dtor
}

void LedPixel::setPosition(ofVec2f& _pos)
{
    pos = _pos;
}

void LedPixel::set3DPosition(ofVec3f& _pos)
{
    pos3D = _pos;
}

void LedPixel::setBrightness(float value)
{

}

unsigned char LedPixel::getDMXValue(int idx)
{
    if((idx >=0) && (idx < 3)) {
        float tmpval = brightness * (float) col[idx];
        tmpval = ofClamp(tmpval,0,255.0f);
        unsigned char val = (int) tmpval;
        return val;
    }
    return 0;
}
