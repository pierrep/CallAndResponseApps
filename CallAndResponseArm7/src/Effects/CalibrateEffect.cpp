#include "CalibrateEffect.h"

CalibrateEffect::CalibrateEffect()
{
    name = "Calibrate";
    parameters.setName(name + baseName);
    parameters.add(orientation.set( "Orientation", false ));
}

CalibrateEffect::~CalibrateEffect()
{

}

void CalibrateEffect::setup()
{

}

void CalibrateEffect::begin()
{
    if(!bEnabled) return;
}

void CalibrateEffect::update(float curTime)
{
    if(!bEnabled) return;

    BaseEffect::update(curTime);

//    linePos1 = ofVec2f(mouseX-400,0);
//    linePos2

}

void CalibrateEffect::draw(float x, float y, float w, float h)
{
    if(!bEnabled) return;

    ofPushStyle();

    ofSetLineWidth(15);
    if(orientation) {
        ofDrawLine(mouseX-400,0,mouseX-400,900);
    } else {
        ofDrawLine(0,mouseY,1200,mouseY);
    }

    ofPopStyle();

}
