#include "ImagePan.h"

ImagePan::ImagePan()
{
    name = "Image Pan";
    parameters.setName(name + baseName);
    //parameters.add(imagename.set());
    parameters.add(pan_speed.set("Pan speed", 1000,500,3000));
    ofxKeyframeAnimRegisterEvents(this);
    numImgs  = 0;
    bFlip = false;
}

ImagePan::~ImagePan()
{

}

void ImagePan::keyPressed(ofKeyEventArgs& args)
{
    if(args.key == OF_KEY_RIGHT) {
        data->currentPaletteImage++;
        if(data->currentPaletteImage >= numImgs) data->currentPaletteImage = 0;
    } else if(args.key == OF_KEY_LEFT) {
        data->currentPaletteImage--;
        if(data->currentPaletteImage < 0) data->currentPaletteImage = numImgs-1;
    }

}

void ImagePan::setup()
{


}

void ImagePan::begin()
{
    if(!bEnabled) return;
    data->bUseFrameBuffer = true;    

    height = 0;
    bEndSequence = false;
    bDoRotate = false;
    currentTree = data->currentTree;

    timeline.clear();
    timeline.addKeyFrame(Action::tween(pan_speed.get(), &height, effectHeight, TWEEN_QUAD,TWEEN_EASE_OUT));
    timeline.addKeyFrame(Action::pause(1000.0f));
    timeline.addKeyFrame(Action::event(this,"rotate"));
    timeline.addKeyFrame(Action::pause(5000.0f));
    timeline.addKeyFrame(Action::event(this,"finished"));

    angle = ofRandom(0,360);
    adder = 1.0f;
    if(ofRandomf() > 0.5f) {
        bFlip = !bFlip;
    }
}

void ImagePan::onKeyframe(ofxPlaylistEventArgs& args)
{
    // this check is only necessary if you want to be absolutely sure that the onKeyFrame Event was sent by the same object as the receiver.
    if (args.pSender != static_cast<void*>(this)) return;
    //ofLog(OF_LOG_VERBOSE) << "Keyframe Event received for (" << args.pSender << "): " << args.message << ": " << ofGetFrameNum();

    if(args.message == "finished") {
        bEndSequence = true;
    }
    if(args.message == "rotate") {
        //bDoRotate = true;
    }
}

void ImagePan::update(float curTime)
{
    if(!bEnabled) return;

    BaseEffect::update(curTime);

    if(bEndSequence) {
        data->trees[currentTree]->doPixelFade();
		data->trees[currentTree]->clearBufferPixels();
		data->trees[data->tree2]->doPixelFade();
		data->trees[data->tree2]->clearBufferPixels();
		data->trees[data->tree3]->doPixelFade();
		data->trees[data->tree3]->clearBufferPixels();
		data->trees[data->tree4]->doPixelFade();
		data->trees[data->tree4]->clearBufferPixels();
        bEndSequence = false;
        data->bUseFrameBuffer = false;
    }

    if(bDoRotate) {
        angle += adder;
    }

}

void ImagePan::draw(float x, float y, float w, float h)
{
    if(!bEnabled) return;

    ofPushMatrix();
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofTranslate(data->paletteImage[data->currentPaletteImage].getWidth()/2,effectHeight - height + data->paletteImage[data->currentPaletteImage].getHeight()/2);
    ofRotateZDeg(angle);
    if(bFlip) {
        ofRotateZDeg(180);
    }

    data->paletteImage[data->currentPaletteImage].draw(0,0);
    ofPopStyle();
    ofPopMatrix();

}
