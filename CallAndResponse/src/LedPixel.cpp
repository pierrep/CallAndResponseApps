#include "LedPixel.h"

using namespace Playlist;

LedPixel::LedPixel()
{
    col = ofColor::black;
    col = ofColor::red;
    brightness = 1.0f;
    //playlist = new ofxPlaylist();
}

//--------------------------------------------------------------
LedPixel::~LedPixel()
{
    //dtor
    //if(playlist) delete playlist;
    //playlist = Null;
}

//--------------------------------------------------------------
//LedPixel::LedPixel(const LedPixel& obj)
//{
//    col = obj.col;
//    brightness = obj.brightness;
//    //playlist = new ofxPlaylist();
//    //*playlist = *obj.playlist;
//    //playlist = (obj.playlist);
//}

//--------------------------------------------------------------
void LedPixel::fadeOn(int i)
{
    brightness = 0.0f;
    col.r = 1.0f;
    playlist.addKeyFrame(Action::pause(i*100.0f));
    playlist.addKeyFrame(Action::tween(200.f, &brightness, 1.0f,TWEEN_QUAD,TWEEN_EASE_IN));
    playlist.addToKeyFrame(Action::tween(200.0f,200.f,&brightness, 0.0f, TWEEN_QUAD, TWEEN_EASE_OUT));

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
