#include "Animations.h"

Animations::Animations()
{
    curTime = ofGetElapsedTimeMillis();
    prevTime = curTime;
    testPattern = 3;

    pixelIndex = 0;

}

void Animations::setup(TreeData * _data)
{
    data = _data;
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
            data->currentLight = (int) (pixelIndex / NUM_PIXELS_PER_FIXTURE);
            int pIdx = pixelIndex - (data->currentLight * NUM_PIXELS_PER_FIXTURE);
            data->trees[data->currentTree]->lights[data->currentLight]->pixels[pIdx]->setColour(ofColor::chartreuse);
            data->trees[data->currentTree]->lights[data->currentLight]->pixels[pIdx]->setBrightness(1.0f);
            pixelIndex++;
            if(pixelIndex > (5*NUM_PIXELS_PER_FIXTURE - 1)) pixelIndex = 0;
        } else if(testPattern == 3) {
            for(int i = 0;i < data->trees[data->currentTree]->lights.size();i++)
            {
                data->trees[data->currentTree]->lights[i]->setColour(data->colour);
                data->trees[data->currentTree]->lights[i]->setBrightness(data->brightness);

                for(int j = 0; j < data->trees[data->currentTree]->lights[i]->pixels.size();j++) {
                    //float b = ofRandomuf();
                    //data->trees[data->currentTree]->lights[i]->pixels[j]->setBrightness(b);
                }
            }
        }
        else if(testPattern == 4) {
            for(int i = 0;i < data->trees[data->currentTree]->lights.size();i++)
            {
                data->trees[data->currentTree]->lights[i]->setColour(data->colour);

                //data->trees[data->currentTree]->lights[i]->setBrightness(brightness);
//                for(int j = 0; j < data->trees[data->currentTree]->lights[i]->pixels.size();j++) {
//                    float b = ofRandomuf();
//                    data->trees[data->currentTree]->lights[i]->pixels[j]->setBrightness(b);
//                }
            }
        }

    }

}

