#include "GuiMap.h"


GuiMap::GuiMap()
{

    currentTree = 0;
    circleRadius = 15.0f;

    disableMouseEvents();
    disableKeyEvents();
    fbo.allocate(400,900);
}

GuiMap::~GuiMap()
{
    //dtor
}

void GuiMap::setup(vector<Tree *> * _trees)
{
    trees = _trees;

    mapImg.load("Gui/Westgarth.png");
}

void GuiMap::draw()
{
    draw(0,0,ofGetWidth(),ofGetHeight());
}

void GuiMap::draw(float x, float y, float w, float h)
{
    fbo.begin();
    ofPushStyle();
    ofClear(255,255,255, 0);
    mapImg.draw(0,0,fbo.getWidth(),fbo.getHeight());

    ofSetRectMode(OF_RECTMODE_CENTER);
    for(int j=0; j < trees->size();j++)
    {
        /* Draw circle */
        ofVec2f pos = trees->at(j)->getMapPos();
        if(currentTree == j) {
            ofSetColor(255,0,0);
        } else {
            ofSetColor(200,200,200);
        }
        ofDrawCircle(pos,circleRadius);
    }


    ofPopStyle();
    fbo.end();

    fbo.draw(x,y,w,h);
}

void GuiMap::keyPressed(ofKeyEventArgs& args)
{

}

void GuiMap::mousePressed(ofMouseEventArgs& args)
{
    float distance = 10000;
    int id = 0;
    ofVec2f p = ofVec2f(args.x,args.y);
    for(int j=0; j < trees->size();j++)
    {
        ofVec2f pos = trees->at(currentTree)->getMapPos();
        float dist = p.distance(pos);
        if(dist < distance ) {
            distance = dist;
            id = j;
        }

    }
    if(distance < circleRadius/2) {
        currentTree = id;
    }
}

void GuiMap::mouseDragged(ofMouseEventArgs& args)
{

}

void GuiMap::mouseMoved(ofMouseEventArgs& args) {

}

void GuiMap::mouseReleased(ofMouseEventArgs& args) {

}

void GuiMap::enableMouseEvents() {
    ofAddListener(ofEvents().mousePressed, this, &GuiMap::mousePressed);
    ofAddListener(ofEvents().mouseMoved, this, &GuiMap::mouseMoved);
    ofAddListener(ofEvents().mouseDragged, this, &GuiMap::mouseDragged);
    ofAddListener(ofEvents().mouseReleased, this, &GuiMap::mouseReleased);
}

void GuiMap::disableMouseEvents() {
    ofRemoveListener(ofEvents().mousePressed, this, &GuiMap::mousePressed);
    ofRemoveListener(ofEvents().mouseMoved, this, &GuiMap::mouseMoved);
    ofRemoveListener(ofEvents().mouseDragged, this, &GuiMap::mouseDragged);
    ofRemoveListener(ofEvents().mouseReleased, this, &GuiMap::mouseReleased);
}

void GuiMap::enableKeyEvents() {
    ofAddListener(ofEvents().keyPressed, this, &GuiMap::keyPressed);
    //ofAddListener(ofEvents().keyReleased, this, &GuiMap::keyReleased);
}

void GuiMap::disableKeyEvents() {
    ofRemoveListener(ofEvents().keyPressed, this, &GuiMap::keyPressed);
    //ofRemoveListener(ofEvents().keyReleased, this, &GuiMap::keyReleased);
}
