#include "Animations.h"
#include "Tree.h"
#include "LedFixture.h"
#include "Effects/BaseEffect.h"
#include "Effects/BloomEffect.h"
#include "Effects/NoiseEffect.h"
#include "Effects/LineEffect.h"
#include "Effects/LineEffect2.h"
#include "Effects/NoiseParticlesEffect.h"
#include "Effects/CalibrateEffect.h"
#include "Effects/ImagePan.h"
#include "Effects/TrailParticles.h"

Animations::Animations()
{
    pattern = 0;
    pixelIndex = 0;
    currentFx = 0;

    #ifdef USE_GUI
    ofxDatGui::setAssetPath("../../../../../addons/ofxDatGui/");
    #endif

    fxframe.allocate(1200,900,GL_RGBA);
    
	/* PBO optimisation */
	bUsePBO = false;
	bReadyToSend = true;
    #if !defined(TARGET_RASPBERRY_PI)
    bUsePBO = true;
    pixelBufferBack.allocate(1200*900*4,GL_DYNAMIC_READ);
    pixelBufferFront.allocate(1200*900*4,GL_DYNAMIC_READ);
	#endif 
	
    effect.push_back(new CalibrateEffect());
    effect.push_back(new BloomEffect());
    effect.push_back(new ImagePan());
    effect.push_back(new LineEffect());
    effect.push_back(new LineEffect2());
    effect.push_back(new TrailParticles());
    effect.push_back(new NoiseParticlesEffect());

    effect.push_back(new NoiseEffect());
    effect.back()->setResolution(400,300);

	fxframe.readToPixels(framePixels);
}

Animations::~Animations()
{
    for (std::vector< BaseEffect *>::iterator itr = effect.begin() ; itr != effect.end(); ++itr)
    {
      delete (*itr);
    }
    effect.clear();
}

void Animations::setup(TreeData * _data)
{
    data = _data;
    for(unsigned int i =0;i < effect.size();i++) {
        effect[i]->setData(data);
        effect[i]->setup();
        effect[i]->setupGui();
        effect[i]->enable(false);
        ofLogNotice("FX") << "Added: " << effect[i]->getName();
    }

    effect[currentFx]->enable(true);
}

void Animations::setPattern(int i)
{
    pattern = i;
    data->currentLight = 0;
    pixelIndex = 0;
}

void Animations::update(float curTime)
{
    for(unsigned int i =0;i < effect.size();i++)
    {
        effect[i]->update(curTime);
    }

    if(pattern == 0) {

        if(data->bUseFrameBuffer) {
			if (bUsePBO) {
				#ifdef TARGET_RASPBERRY_PI
				fxframe.readToPixels(framePixels);
				#else
				fxframe.getTexture().copyTo(pixelBufferBack);
				pixelBufferFront.bind(GL_PIXEL_UNPACK_BUFFER);
				unsigned char * pix = pixelBufferFront.map<unsigned char>(GL_READ_ONLY);
                framePixels.setFromExternalPixels(pix,fxframe.getWidth(),fxframe.getHeight(),OF_PIXELS_RGBA);
				pixelBufferFront.unmap();
				swap(pixelBufferBack,pixelBufferFront);
				pixelBufferFront.unbind(GL_PIXEL_UNPACK_BUFFER);
				#endif
			}
			else {
				fxframe.readToPixels(framePixels);
			}
			
			if (bReadyToSend) 
			{
				for (unsigned int i = 0; i < data->trees[data->currentTree]->lights.size(); i++)
				{
					for (unsigned int j = 0; j < data->trees[data->currentTree]->lights[i]->pixels.size(); j++) {
						int x = (int)data->trees[data->currentTree]->lights[i]->pixels[j]->getPosition().x;
						int y = (int)data->trees[data->currentTree]->lights[i]->pixels[j]->getPosition().y;
                        int index = (x + (y - 1)*fxframe.getWidth()) * 4;
						ofColor c = ofColor(framePixels[index], framePixels[index + 1], framePixels[index + 2]);

						data->trees[data->currentTree]->lights[i]->pixels[j]->setColour(c);
					}
					data->trees[data->currentTree]->lights[i]->setBrightness(data->brightness);
				}

				if (data->tree2 != -1) 
				{
					for (unsigned int i = 0; i < data->trees[data->tree2]->lights.size(); i++)
					{
						for (unsigned int j = 0; j < data->trees[data->tree2]->lights[i]->pixels.size(); j++) {
							int x = (int)data->trees[data->tree2]->lights[i]->pixels[j]->getPosition().x;
							int y = (int)data->trees[data->tree2]->lights[i]->pixels[j]->getPosition().y;
                            int index = (x + (y - 1)*fxframe.getWidth()) * 4;
							ofColor c = ofColor(framePixels[index], framePixels[index + 1], framePixels[index + 2]);

							data->trees[data->tree2]->lights[i]->pixels[j]->setColour(c);
						}
						data->trees[data->tree2]->lights[i]->setBrightness(data->brightness);
					}
				}
				if (data->tree3 != -1)
				{
					for (unsigned int i = 0; i < data->trees[data->tree3]->lights.size(); i++)
					{
						for (unsigned int j = 0; j < data->trees[data->tree3]->lights[i]->pixels.size(); j++) {
							int x = (int)data->trees[data->tree3]->lights[i]->pixels[j]->getPosition().x;
							int y = (int)data->trees[data->tree3]->lights[i]->pixels[j]->getPosition().y;
                            int index = (x + (y - 1)*fxframe.getWidth()) * 4;
							ofColor c = ofColor(framePixels[index], framePixels[index + 1], framePixels[index + 2]);

							data->trees[data->tree3]->lights[i]->pixels[j]->setColour(c);
						}
						data->trees[data->tree3]->lights[i]->setBrightness(data->brightness);
					}
				}
				if (data->tree4 != -1)
				{
					for (unsigned int i = 0; i < data->trees[data->tree4]->lights.size(); i++)
					{
						for (unsigned int j = 0; j < data->trees[data->tree4]->lights[i]->pixels.size(); j++) {
							int x = (int)data->trees[data->tree4]->lights[i]->pixels[j]->getPosition().x;
							int y = (int)data->trees[data->tree4]->lights[i]->pixels[j]->getPosition().y;
                            int index = (x + (y - 1)*fxframe.getWidth()) * 4;
							ofColor c = ofColor(framePixels[index], framePixels[index + 1], framePixels[index + 2]);

							data->trees[data->tree4]->lights[i]->pixels[j]->setColour(c);
						}
						data->trees[data->tree4]->lights[i]->setBrightness(data->brightness);
					}
				}
			}
			else {
				bReadyToSend = true;
			}
        }

    } else {
        testPattern();
    }

}

void Animations::updateFBO()
{
    fxframe.begin();
        ofClear(0,0,0,0);
        for(int i = 0; i < activeFx.size();i++) {
            activeFx[i]->draw(0,0,1200,900);
        }
    fxframe.end();
}

void Animations::updateActiveEffectPos(ofVec2f pos)
{
    for(int i = 0; i < activeFx.size();i++) {
        activeFx[i]->updateMouse(pos);
    }
}

void Animations::draw(float x, float y)
{
    fxframe.draw(x,y,1200,900);
}

void Animations::drawGui()
{
    effect[currentFx]->drawGui();
}

void Animations::begin()
{
    for(int i = 0; i < activeFx.size();i++) {
        activeFx[i]->begin();
    }
}

void Animations::enableEffect(const string name)
{
    int index = -1;
    for(int i = 0;i < effect.size();i++)
    {
        if(effect[i]->getName() == name) {
            index = i;
            break;
        }
    }
    if(index >= 0) {
        enableEffect(index);
    }
}

void Animations::clearActiveEffects()
{
    for(int i =0;i < effect.size();i++)
    {
        effect[i]->enable(false);
    }
    activeFx.clear();
}

void Animations::enableEffect(int index)
{
    index = ofClamp(index, 0, effect.size()-1);
    currentFx = index;
    if(effect[index]->isEnabled() == false) {
        activeFx.push_back(effect[index]);
        effect[index]->enable(true);
    }
	bReadyToSend = false;
}


void Animations::nextEffect()
{
    clearActiveEffects();

    currentFx++;
    if(currentFx >= effect.size()) {
        currentFx = 0;
    }

    for(int i =0;i < effect.size();i++)
    {
        effect[i]->enable(false);
    }

    enableEffect(currentFx);
    effect[currentFx]->begin();
    effect[currentFx]->enable(true);
}

void Animations::save()
{
    for(int i = 0;i < effect.size();i++) {
        settings.clear();
        settings.serialize(effect[i]->parameters);
        settings.save("EffectSettings/"+effect[i]->parameters.getName()+".xml");
    }

}

void Animations::load()
{
    for(int i = 0;i < effect.size();i++) {
        settings.clear();
        settings.load("EffectSettings/"+effect[i]->parameters.getName()+".xml");
        settings.deserialize(effect[i]->parameters);
    }

}

void Animations::testPattern()
{
    if(pattern == 1) {
        if(ofGetFrameNum()%10 == 0) {
            data->trees[data->currentTree]->clear();
            data->trees[data->currentTree]->lights[data->currentLight]->setColour(ofColor::purple);
            data->trees[data->currentTree]->lights[data->currentLight]->setBrightness(1.0f);
            data->currentLight++;
            if(data->currentLight > data->trees[data->currentTree]->lights.size()-1) data->currentLight = 0;
        }
    }
    else if(pattern == 2) {
        if(ofGetFrameNum()%5 == 0) {
            data->trees[data->currentTree]->clear();
            data->currentLight = (pixelIndex / NUM_PIXELS_PER_FIXTURE);
            unsigned int idx = pixelIndex - (data->currentLight * NUM_PIXELS_PER_FIXTURE);
            data->trees[data->currentTree]->lights[data->currentLight]->pixels[idx]->setColour(ofColor::chartreuse);
            data->trees[data->currentTree]->lights[data->currentLight]->pixels[idx]->setBrightness(1.0f);
            pixelIndex++;
            if(pixelIndex > (data->trees[data->currentTree]->lights.size()* NUM_PIXELS_PER_FIXTURE - 1)) pixelIndex = 0;
        }
    } else if(pattern == 3) {
        for(unsigned int i = 0;i < data->trees[data->currentTree]->lights.size();i++)
        {
            data->trees[data->currentTree]->lights[i]->setColour(data->colour);
            data->trees[data->currentTree]->lights[i]->setBrightness(data->brightness);
        }
    }
    else if(pattern == 4) {
        for(unsigned int i = 0;i < data->trees[data->currentTree]->lights.size();i++)
        {
            data->trees[data->currentTree]->lights[i]->setColour(data->colour);
        }
    }
}
