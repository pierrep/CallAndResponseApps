#include "PerlinNoiseEffect.h"

PerlinNoiseEffect::PerlinNoiseEffect()
{
    name = "PerlinNoise";
    parameters.setName(name + baseName);
    /*parameters.add(resolution.set( "Resolution", 512, 2, 64 ));
    parameters.add(noiseFrequency.set( "Noise Frequency", 20.0f, 0.00001f, 4096.0f ));
    parameters.add(animate.set( "Animate", true ));
    parameters.add(doThreshold.set( "Threshold", false ));
    parameters.add(thresholdLow.set( "Treshold Low", 0, 0, 255 ));
    parameters.add(thresholdHigh.set( "Treshold High", 127, 0, 255 ));
    parameters.add(invert.set( "Invert Threshold", false ));
	*/
}

PerlinNoiseEffect::~PerlinNoiseEffect()
{

}

void PerlinNoiseEffect::setup()
{

    shader.load("","Shaders/3DperlinNoise.frag");


}

void PerlinNoiseEffect::begin()
{
    if(!bEnabled) return;
    data->bUseFrameBuffer = true;
}

void PerlinNoiseEffect::update(float curTime)
{
    if(!bEnabled) return;

    BaseEffect::update(curTime);


}


void PerlinNoiseEffect::draw(float x, float y, float w, float h)
{
    if(!bEnabled) return;

   // ofSetColor(0,255,0);
   // ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());

    ofSetColor(255);
    shader.begin();
    shader.setUniform1f("u_time", ofGetElapsedTimef());
    shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());
    shader.end();

}
