#include "BloomEffect.h"

BloomEffect::BloomEffect()
{
    name = "Bloom";
    parameters.setName(name + baseName);
    parameters.add(maxradius.set( "Max radius", 300, 100, 500 ));
    parameters.add(bloomspeed.set("Bloom speed", 1000,500,3000));

    //c1.set(255,0,255);
	c1.set(230, 1, 16);
    //c1.setHex(0x6B6100);
    //c2.set(0x811400);
    c2.set(0,0,255);

    pixelIndex = 0;
}

BloomEffect::~BloomEffect()
{

}

void BloomEffect::setup()
{

}

void BloomEffect::begin()
{
    if(!bEnabled) return;
    data->bUseFrameBuffer = true;

    radius = 0;
    ratio = 0;

    timeline.clear();
    timeline.addKeyFrame(Action::tween(bloomspeed.get(), &radius, maxradius.get(),TWEEN_QUAD,TWEEN_EASE_OUT));
    timeline.addKeyFrame(Action::pause(3000.0f));
    timeline.addKeyFrame(Action::tween(3000.0f,&radius, 0.0f, TWEEN_QUAD, TWEEN_EASE_IN));
    timeline.addToKeyFrame(Action::tween(2000.0f, &ratio, 1.0f,TWEEN_QUAD,TWEEN_EASE_IN));
}

void BloomEffect::update(float curTime)
{
    if(!bEnabled) return;

    BaseEffect::update(curTime);

}

void BloomEffect::draw(float x, float y, float w, float h)
{
    if(!bEnabled) return;

    ofPushStyle();

    ofSetColor(c1.getLerped(c2,ratio),255.0f - 255.0f*ratio + 100.0f);
    ofDrawCircle(x + 600, ofGetHeight()/2, radius);
    ofPopStyle();
}
