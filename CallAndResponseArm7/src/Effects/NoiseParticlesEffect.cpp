#include "NoiseParticlesEffect.h"

NoiseParticlesEffect::NoiseParticlesEffect()
{
    name = "Noise Particles";
    parameters.setName(name + baseName);

}

NoiseParticlesEffect::~NoiseParticlesEffect()
{

}

void NoiseParticlesEffect::setup()
{
    for(int i = 0; i < MAX_PARTICLES; i++)
    {
        NoiseParticle p((float)i/10000.0f);
        flow.push_back(p);
    }
}

void NoiseParticlesEffect::begin()
{
    if(!bEnabled) return;
    for (int i = 0; i < flow.size(); i++)
    {
        flow.at(i).reset();
    }
}

void NoiseParticlesEffect::update(float curTime)
{
    if(!bEnabled) return;

    BaseEffect::update(curTime);

}

void NoiseParticlesEffect::draw(float x, float y, float w, float h)
{
    if(!bEnabled) return;

    drawFlowfield();
}

void NoiseParticlesEffect::drawFlowfield()
{

    // set global variables that influence the particle flow's movement
    globalX = ofNoise(ofGetFrameNum() * 0.01) * effectHeight/2 + effectWidth/4;
    globalY = ofNoise(ofGetFrameNum() * 0.005 + 5) * effectHeight;

    // update and display all particles in the flow
    glPointSize(6.0f);

    float w = effectWidth;
    float h = effectHeight;

    for (int i = 0; i < flow.size(); i++)
    {
        flow.at(i).update(globalX,globalY,w,h);
        flow.at(i).updateVertexArrays(w, h, i, posArray, colArray);
    }

    ofPushStyle();
    //ofEnableBlendMode(OF_BLENDMODE_ADD);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, posArray);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colArray);

    glDrawArrays(GL_POINTS, 0, MAX_PARTICLES * 2);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    ofPopStyle();

}
