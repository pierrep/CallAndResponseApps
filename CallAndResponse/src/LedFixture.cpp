#include "LedFixture.h"

LedFixture::LedFixture()
{
    id = 0;
    pos = ofVec2f::zero();
    bIsDirty = false;
}

//--------------------------------------------------------------
LedFixture::~LedFixture()
{
    for (std::vector< LedPixel *>::iterator itr = pixels.begin() ; itr != pixels.end(); ++itr)
    {
      delete (*itr);
    }
    pixels.clear();
}

void LedFixture::clear()
{
    for(int i = 0;i < pixels.size();i++)
    {
        pixels[i]->clear();
    }
   // bIsDirty = false;
}

void LedFixture::setupPixels(ofVec2f pos, float _pixelWidth)
{
    pixelWidth = _pixelWidth;

    for(int i=0; i < NUM_PIXELS_PER_FIXTURE; i++) {
        LedPixel* p = new LedPixel();
        p->setId((id -1)*NUM_PIXELS_PER_FIXTURE + i);
        float y = pos.y + i*(pixelWidth+1);
        ofVec2f v = ofVec2f(pos.x , y);
        p->setPosition(v);
        pixels.push_back(p);
    }
}

//--------------------------------------------------------------
void LedFixture::setPosition(ofVec2f _pos)
{
    pos = _pos;
    ofVec2f pixpos = pos;
    for(int k=0; k < pixels.size(); k++)
    {
        pixels[k]->setPosition(pixpos);
        pixpos.y = pixpos.y + pixelWidth+1;
    }
}

//--------------------------------------------------------------
void LedFixture::setColour(ofColor c)
{
    for(int i = 0;i < pixels.size();i++)
    {
        pixels[i]->setColour(c);
    }
}

//--------------------------------------------------------------
void LedFixture::setBrightness(float val)
{
    for(int i = 0;i < pixels.size();i++)
    {
        pixels[i]->setBrightness(val);
    }
}

//--------------------------------------------------------------
void LedFixture::fadeOn(float time)
{
    for(int i = 0;i < pixels.size();i++)
    {
        pixels[i]->fadeOn(time);
    }
}

//--------------------------------------------------------------
bool LedFixture::update()
{
    bool val = false;
    unsigned int count = 0;
    for(unsigned int i = 0;i < pixels.size();i++)
    {
        val = pixels[i]->update();
        if(val) {
            bIsDirty = true;
        }
        else {
            count++;
        }
    }
    if (count >= pixels.size())
        bIsDirty = false;

    return bIsDirty;
}

//--------------------------------------------------------------
void LedFixture::draw()
{

}
