#include "ImagePan.h"

ImagePan::ImagePan()
{
    name = "Image Pan";
    parameters.setName(name + baseName);
    //parameters.add(imagename.set());
    parameters.add(pan_speed.set("Pan speed", 1000,500,3000));
    ofxKeyframeAnimRegisterEvents(this);
}

ImagePan::~ImagePan()
{

}

void ImagePan::setup()
{
    image.load("EffectSettings/images/panner.png");

}

void ImagePan::begin()
{
    if(!bEnabled) return;
    data->bUseFrameBuffer = true;

    height = 100;
    bEndSequence = false;
    currentTree = data->currentTree;

    timeline.clear();
    timeline.addKeyFrame(Action::tween(pan_speed.get(), &height, 1200, TWEEN_QUAD,TWEEN_EASE_OUT));
    timeline.addKeyFrame(Action::pause(3000.0f));
    timeline.addKeyFrame(Action::event(this,"finished"));

}

void ImagePan::onKeyframe(ofxPlaylistEventArgs& args)
{
    // this check is only necessary if you want to be absolutely sure that
    // the onKeyFrame Event was sent by the same object as the receiver.
    if (args.pSender != static_cast<void*>(this)) return;

    //ofLog(OF_LOG_VERBOSE) << "Keyframe Event received for (" << args.pSender << "): " << args.message << ": " << ofGetFrameNum();
    if(args.message == "finished") {
        bEndSequence = true;
    }

}

void ImagePan::update(float curTime)
{
    if(!bEnabled) return;

    BaseEffect::update(curTime);

    if(bEndSequence) {
        data->trees[currentTree]->doPixelFade();
        bEndSequence = false;
        //bShowImage = false;
        data->bUseFrameBuffer = false;
    }

}

void ImagePan::draw(float x, float y, float w, float h)
{
    if(!bEnabled) return;

    image.draw(0,1200-height);
}
