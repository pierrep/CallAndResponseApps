#include "BaseEffect.h"

BaseEffect::BaseEffect()
{
    enableEditing();
    bToggle = false;
    bEnabled = false;
    baseName = " Effect Settings";
}

void BaseEffect::setupGui()
{
        paramfolder = new ofxDatGuiFolder(ofToUpper(parameters.getName()), ofColor::green);
        ofParameterGroup& p = parameters;
        for(int i = 0; i < p.size();i++) {
            if(p.getType(i) == "11ofParameterIfE") {
                paramfolder->addSlider(p.getFloat(i));
            }
            else if(p.getType(i) == "11ofParameterIiE") {
                paramfolder->addSlider(p.getInt(i));
            }
            else if(p.getType(i) == "11ofParameterIbE") {
                paramfolder->addToggle(p.getBool(i));
            }
        }
//        int pad = 10 - p.size();
//        if(pad < 0) pad = 0;
//        for(int i = 0; i < pad;i++) {
//            paramfolder->addLabel("");
//        }
        paramfolder->expand();

        float pad = 300.0f - paramfolder->getHeight();
        if(pad < 0) pad = 0.0f;
        paramfolder->addBreak()->setHeight(pad);


        paramfolder->setPosition(ofGetWidth() - paramfolder->getWidth(), 400);
}

void BaseEffect::update(float time)
{
    paramfolder->update();
}

void BaseEffect::drawGui()
{
    paramfolder->setPosition(ofGetWidth() - paramfolder->getWidth(), ofGetHeight() - paramfolder->getHeight());
    paramfolder->draw();
}


void BaseEffect::keyPressed(ofKeyEventArgs& args)
{
    if(args.key == 't') {
        bToggle = !bToggle;
    }
}

void BaseEffect::mousePressed(ofMouseEventArgs& args)
{

}

void BaseEffect::mouseDragged(ofMouseEventArgs& args)
{

}

void BaseEffect::mouseMoved(ofMouseEventArgs& args) {
    mouseX = args.x;
    mouseY = args.y;
}

void BaseEffect::mouseReleased(ofMouseEventArgs& args) {

}

void BaseEffect::enableEditing() {
    ofAddListener(ofEvents().mousePressed, this, &BaseEffect::mousePressed);
    ofAddListener(ofEvents().mouseMoved, this, &BaseEffect::mouseMoved);
    ofAddListener(ofEvents().mouseDragged, this, &BaseEffect::mouseDragged);
    ofAddListener(ofEvents().mouseReleased, this, &BaseEffect::mouseReleased);

    ofAddListener(ofEvents().keyPressed, this, &BaseEffect::keyPressed);
    //ofAddListener(ofEvents().keyReleased, this, &BaseEffect::keyReleased);
}

void BaseEffect::disableEditing() {
    ofRemoveListener(ofEvents().mousePressed, this, &BaseEffect::mousePressed);
    ofRemoveListener(ofEvents().mouseMoved, this, &BaseEffect::mouseMoved);
    ofRemoveListener(ofEvents().mouseDragged, this, &BaseEffect::mouseDragged);
    ofRemoveListener(ofEvents().mouseReleased, this, &BaseEffect::mouseReleased);

    ofRemoveListener(ofEvents().keyPressed, this, &BaseEffect::keyPressed);
    //ofRemoveListener(ofEvents().keyReleased, this, &BaseEffect::keyReleased);

}


