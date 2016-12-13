#include "EmptyEffect.h"

EmptyEffect::EmptyEffect()
{
    name = "Empty";
    parameters.setName(name + baseName);


}

EmptyEffect::~EmptyEffect()
{

}

void EmptyEffect::setup()
{

}

void EmptyEffect::begin()
{
    if(!bEnabled) return;
}

void EmptyEffect::update(float curTime)
{
    if(!bEnabled) return;

    BaseEffect::update(curTime);

}

void EmptyEffect::draw(float x, float y, float w, float h)
{
    if(!bEnabled) return;
}
