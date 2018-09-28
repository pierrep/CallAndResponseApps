#include "TrailParticles.h"

TrailParticles::TrailParticles()
{
    name = "Trail Particles";
    parameters.setName(name + baseName);
	startPos = 400;

}

TrailParticles::~TrailParticles()
{

}

void TrailParticles::setup()
{
	billboards.getVertices().resize(NUM_BILLBOARDS);
	billboards.getColors().resize(NUM_BILLBOARDS);
	billboards.getNormals().resize(NUM_BILLBOARDS,ofVec3f(0));
	
	billboards.setUsage( GL_DYNAMIC_DRAW );
	billboards.setMode(OF_PRIMITIVE_POINTS);

	#if defined(TARGET_RASPBERRY_PI)
	//ofLogNotice() << "Load GLES shaders";
	//billboardShader.load("Shaders/BillboardGLES";
	#else
	//billboardShader.load("Shaders/Billboard");
	#endif
	glPointSize(4);

    parameters.add(duration.set( "FadeThreshold", 1500.0f, 1000.0f, 4000.0f ));
    parameters.add(speed.set( "Speed", 0.4f, 0.1f, 1.0f ));
	
}

void TrailParticles::begin()
{
    if(!bEnabled) return;
    data->bUseFrameBuffer = true;

    currentTree = data->currentTree;
    curTime = ofGetElapsedTimeMillis();
    prevTime = curTime;
    bPlayAnim = true;
    ofLogVerbose() << "Trail Particles BEGIN";

    for (int unsigned i=0; i<NUM_BILLBOARDS; i++)
    {
        if(data->direction == 1) {
            billboardVels[i].set(ofRandomf()*5, 0.0, 0);
            billboards.getVertices()[i] = glm::vec3(startPos, ofRandom(100, 800), 0);
        } else {
            billboardVels[i].set(ofRandomf()*-5, 0.0, 0);
            billboards.getVertices()[i] = glm::vec3(1200 - startPos, ofRandom(100, 800), 0);
        }
		/* set colours - must be in float format */
        billboards.getColors()[i].set(ofColor::fromHsb(ofRandom(190,255), ofRandom(150,255), 255));
        //billboards.getColors()[i].set(230.0f/255.0f, 1.0f/255.0f, 16.0f/255.0f);
    }
}

void TrailParticles::update(float curTime)
{
    if(!bEnabled) return;
    BaseEffect::update(curTime);
    
    curTime = ofGetElapsedTimeMillis();
    if(curTime - prevTime > duration.get()) {
        if(bPlayAnim) {
            bPlayAnim = false;
            data->trees[currentTree]->doFade();
            data->bUseFrameBuffer = false;
        }
    }

    if(bPlayAnim) {
         ofVec3f vec(speed.get(),0,0);
        if(data->direction == -1) {
            vec = -vec;
        }
        for (unsigned int i=0; i<NUM_BILLBOARDS; i++) {
            billboardVels[i] += vec;
            billboards.getVertices()[i] += billboardVels[i];
        }
    }

}

void TrailParticles::draw(float x, float y, float w, float h)
{
    if(!bEnabled) return;

    if(bPlayAnim) {
        ofPushStyle();
        ofSetColor(255);
        ofPushMatrix();

        //billboardShader.begin();

        ofEnablePointSprites();
        billboards.draw();
        ofDisablePointSprites();

        //billboardShader.end();

        ofPopMatrix();
        ofPopStyle();
    }
}
