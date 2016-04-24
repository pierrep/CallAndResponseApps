#include "EmptyEffect.h"

EmptyEffect::EmptyEffect()
{

    parameters.setName("Empty" + baseName);


}

EmptyEffect::~EmptyEffect()
{

}

void EmptyEffect::setup()
{


}

void EmptyEffect::update(float curTime)
{
    if(!bEnabled) return;

    BaseEffect::update(curTime);

}

void EmptyEffect::draw()
{

}

void EmptyEffect::draw(float x, float y, float w, float h)
{
    
}
