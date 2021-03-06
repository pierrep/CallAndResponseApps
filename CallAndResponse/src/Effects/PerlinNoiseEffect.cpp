#include "PerlinNoiseEffect.h"

PerlinNoiseEffect::PerlinNoiseEffect()
{
    name = "PerlinNoise";
    parameters.setName(name + baseName);
    ofxKeyframeAnimRegisterEvents(this);
}

PerlinNoiseEffect::~PerlinNoiseEffect()
{

}

void PerlinNoiseEffect::setup()
{
	#if defined(TARGET_RASPBERRY_PI)
	ofLogNotice() << "Load GLES shaders";
	shader.load("Shaders/3DperlinNoiseGLES.vert","Shaders/3DperlinNoise.frag");
	#else
	shader.load("","Shaders/3DperlinNoise.frag");
	#endif    
}

void PerlinNoiseEffect::onKeyframe(ofxPlaylistEventArgs& args)
{
    // this check is only necessary if you want to be absolutely sure that the onKeyFrame Event was sent by the same object as the receiver.
    if (args.pSender != static_cast<void*>(this)) return;

    if(args.message == "ready") {
        bReady = true;
    }
}

void PerlinNoiseEffect::begin()
{
    if(!bEnabled) return;
    data->bUseFrameBuffer = true;

    colour = data->getRandomPaletteColour();
    colour = data->setSimilarPaletteColourHSB(colour,20);
    bReady = false;
    alpha = 0.0f;

    timeline.clear();
    timeline.addKeyFrame(Action::pause(1500.0f));
    timeline.addKeyFrame(Action::event(this,"ready"));
    timeline.addKeyFrame(Action::tween(1500.0f, &alpha, 1.0f, TWEEN_QUAD,TWEEN_EASE_IN));
}

void PerlinNoiseEffect::update(float curTime)
{
    if(!bEnabled) return;

    BaseEffect::update(curTime);
}


void PerlinNoiseEffect::draw(float x, float y, float w, float h)
{
    if(!bEnabled) return;

    if(bReady) {
        ofSetColor(255);
        shader.begin();
        shader.setUniform1f("u_time", ofGetElapsedTimef());
        shader.setUniform2f("u_resolution", effectWidth, effectHeight);
        shader.setUniform4f("u_colour", colour.r, colour.g, colour.b, alpha);
        #if defined(TARGET_RASPBERRY_PI)
        ofDrawRectangle(200,50,800, 800);
        #else
        ofDrawRectangle(0,0,effectWidth, effectHeight);
        #endif
        shader.end();

    }

}
