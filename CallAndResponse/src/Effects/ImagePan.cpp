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
    for(int i = 0; i < 6; i++) {
        image[i].load("EffectSettings/images/panner"+ofToString(i)+".png");
    }

}

void ImagePan::begin()
{
    if(!bEnabled) return;
    data->bUseFrameBuffer = true;

    currentImage = ofRandom(0,6);

    height = 200;
    bEndSequence = false;
    bDoRotate = false;
    currentTree = data->currentTree;

    timeline.clear();
    timeline.addKeyFrame(Action::tween(pan_speed.get(), &height, effectWidth, TWEEN_QUAD,TWEEN_EASE_OUT));
    timeline.addKeyFrame(Action::pause(1000.0f));
    timeline.addKeyFrame(Action::event(this,"rotate"));
    timeline.addKeyFrame(Action::pause(3000.0f));
    timeline.addKeyFrame(Action::event(this,"finished"));

    angle = 0;
    adder = 1.0f;

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
    if(args.message == "rotate") {
        bDoRotate = true;
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
    ofTranslate(image->getWidth()/2,effectWidth - height + image->getHeight()/2);
    ofRotateZ(angle);
    image[currentImage].draw(0,0);
    ofPopStyle();
    ofPopMatrix();

}
