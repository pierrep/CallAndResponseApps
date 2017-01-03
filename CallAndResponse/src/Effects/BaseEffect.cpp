#include "BaseEffect.h"

BaseEffect::BaseEffect()
{
    enableEditing();
    bToggle = false;
    bEnabled = false;
    baseName = " Effect Settings";
    effectHeight = 900;
    effectWidth = 1200;
    parameters.add(bEnabled.set("Enabled",false));
}

BaseEffect::~BaseEffect()
{
    #ifdef USE_GUI
        delete paramfolder;
    #endif

}

void BaseEffect::setData(TreeData *_data)
{
    data = _data;
}


void BaseEffect::setupGui()
{
#ifdef USE_GUI
        paramfolder = new ofxDatGuiFolder(ofToUpper(parameters.getName()), ofColor::green);
        ofParameterGroup& p = parameters;

        for(int i = 0; i < p.size();i++) {
            if((p.getType(i) == "11ofParameterIfE") || (p.getType(i) == "class ofParameter<float>")) {
                paramfolder->addSlider(p.getFloat(i));
            }
            else if((p.getType(i) == "11ofParameterIiE") || (p.getType(i) == "class ofParameter<int>")) {
                paramfolder->addSlider(p.getInt(i));
            }
            else if((p.getType(i) == "11ofParameterIbE") || (p.getType(i) == "class ofParameter<bool>")) {
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
#endif
}

void BaseEffect::update(float time)
{
#ifdef USE_GUI
    paramfolder->update();
#endif
    timeline.update();
}

void BaseEffect::drawGui()
{
#ifdef USE_GUI
    paramfolder->setPosition(ofGetWidth() - paramfolder->getWidth(), ofGetHeight() - paramfolder->getHeight());
    paramfolder->draw();
#endif
}

const string BaseEffect::getName()
{
    return ofToLower(name);
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


