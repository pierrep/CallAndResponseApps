#include "Animations.h"
#include "Effects/BloomEffect.h"
#include "Effects/NoiseEffect.h"
#include "Effects/CalibrateEffect.h"

Animations::Animations()
{
    curTime = ofGetElapsedTimeMillis();
    prevTime = curTime;
    testPattern = 5;
    currentfx = 0;
    pixelIndex = 0;

    fxframe.allocate(1200,900,GL_RGB);
    effect.push_back(new BloomEffect());
    effect.push_back(new CalibrateEffect());
    effect.push_back(new NoiseEffect());
    effect.back()->setResolution(400,300);
    currentfx = 0;

}

void Animations::setup(TreeData * _data)
{
    data = _data;
    for(int i =0;i < effect.size();i++) {        
        effect[i]->setup();
        effect[i]->setupGui();
        effect[i]->enable(false);
    }
    effect[currentfx]->enable(true);
}

void Animations::setTestPattern(int i)
{
    testPattern = i;
    data->currentLight = 0;
    pixelIndex = 0;
}

void Animations::update()
{
    curTime = ofGetElapsedTimeMillis();

    effect[currentfx]->update(curTime);


    if(curTime - prevTime > 100) {
        prevTime = curTime;

        if(testPattern == 1) {
            data->trees[data->currentTree]->clear();
            data->trees[data->currentTree]->lights[data->currentLight]->setColour(ofColor::purple);
            data->trees[data->currentTree]->lights[data->currentLight]->setBrightness(1.0f);
            data->currentLight++;
            if(data->currentLight > 4) data->currentLight = 0;
        }
        else if(testPattern == 2) {
            data->trees[data->currentTree]->clear();
            data->currentLight = (pixelIndex / NUM_PIXELS_PER_FIXTURE);
            unsigned int idx = pixelIndex - (data->currentLight * NUM_PIXELS_PER_FIXTURE);
            data->trees[data->currentTree]->lights[data->currentLight]->pixels[idx]->setColour(ofColor::chartreuse);
            data->trees[data->currentTree]->lights[data->currentLight]->pixels[idx]->setBrightness(1.0f);
            pixelIndex++;
            if(pixelIndex > (5*NUM_PIXELS_PER_FIXTURE - 1)) pixelIndex = 0;
        } else if(testPattern == 3) {
            for(unsigned int i = 0;i < data->trees[data->currentTree]->lights.size();i++)
            {
                data->trees[data->currentTree]->lights[i]->setColour(data->colour);
                data->trees[data->currentTree]->lights[i]->setBrightness(data->brightness);

                for(unsigned int j = 0; j < data->trees[data->currentTree]->lights[i]->pixels.size();j++) {
                    //float b = ofRandomuf();
                    //data->trees[data->currentTree]->lights[i]->pixels[j]->setBrightness(b);
                }
            }
        }
        else if(testPattern == 4) {
            for(unsigned int i = 0;i < data->trees[data->currentTree]->lights.size();i++)
            {
                data->trees[data->currentTree]->lights[i]->setColour(data->colour);

                //data->trees[data->currentTree]->lights[i]->setBrightness(brightness);
//                for(int j = 0; j < data->trees[data->currentTree]->lights[i]->pixels.size();j++) {
//                    float b = ofRandomuf();
//                    data->trees[data->currentTree]->lights[i]->pixels[j]->setBrightness(b);
//                }
            }
        }
        else if(testPattern == 5) {

            fxframe.readToPixels(p);
            int s = p.size();

            for(unsigned int i = 0;i < data->trees[data->currentTree]->lights.size();i++)
            {
                for(unsigned int j = 0; j < data->trees[data->currentTree]->lights[i]->pixels.size();j++) {
                    int x = data->trees[data->currentTree]->lights[i]->pixels[j]->getPosition().x;
                    int y = data->trees[data->currentTree]->lights[i]->pixels[j]->getPosition().y;
                    int index = ( x + (y-1)*fxframe.getWidth() ) *3;
                    ofColor c = ofColor(p[index],p[index+1], p[index+2]);

                    data->trees[data->currentTree]->lights[i]->pixels[j]->setColour(c);
                }

                data->trees[data->currentTree]->lights[i]->setBrightness(data->brightness);

            }


        }

    }

}

void Animations::draw(float x, float y)
{
    fxframe.begin();
        ofClear(0,0,0, 0);
        effect[currentfx]->draw(0,0,1200,900);

    fxframe.end();

    fxframe.draw(x,y,1200,900);
}

void Animations::drawGui()
{
    effect[currentfx]->drawGui();
}

void Animations::begin()
{
    effect[currentfx]->begin();
}

void Animations::nextEffect()
{
    currentfx++;
    if(currentfx >= effect.size()) {
        currentfx = 0;
    }

    for(int i =0;i < effect.size();i++) {
        effect[i]->enable(false);
    }
    effect[currentfx]->enable(true);
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
