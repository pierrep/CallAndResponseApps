#include "BloomEffect.h"

BloomEffect::BloomEffect()
{

    parameters.setName("Empty Effect Settings");


}

BloomEffect::~BloomEffect()
{

}

void BloomEffect::setup()
{


}

void BloomEffect::update(float curTime)
{
    if(!bEnabled) return;

    BaseEffect::update(curTime);

}

void BloomEffect::draw()
{

}

void BloomEffect::draw(float x, float y, float w, float h)
{
    
}
