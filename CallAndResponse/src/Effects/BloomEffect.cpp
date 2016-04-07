#include "BloomEffect.h"

BloomEffect::BloomEffect()
{

    parameters.setName("Bloom Effect Settings");
    //parameters.add(noiseFrequency.set( "Noise Frequency", 20.0f, 0.00001f, 4096.0f ));

}

BloomEffect::~BloomEffect()
{

}

void BloomEffect::setup()
{


}

void BloomEffect::update(float curTime)
{

}

void BloomEffect::draw()
{

}

void BloomEffect::draw(float x, float y, float w, float h)
{
    ofPushStyle();

    ofSetLineWidth(15);
    if(bToggle) {
        ofDrawLine(mouseX-400,0,mouseX-400,900);
    } else {
        ofDrawLine(0,mouseY,1200,mouseY);
    }

    ofPopStyle();
}
