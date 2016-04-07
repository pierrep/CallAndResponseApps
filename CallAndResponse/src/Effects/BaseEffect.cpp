#include "BaseEffect.h"

BaseEffect::BaseEffect()
{
    enableEditing();
    bToggle = false;
    bEnabled = false;
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


