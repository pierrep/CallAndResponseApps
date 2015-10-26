#include "LedPixel.h"

LedPixel::LedPixel()
{
    //ctor
}

LedPixel::~LedPixel()
{
    //dtor
}

void LedPixel::setPosition(vector<oVec3f>& _pos)
{
    pos = _pos;
}
