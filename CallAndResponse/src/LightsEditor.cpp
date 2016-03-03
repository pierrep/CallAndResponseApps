#include "LightsEditor.h"


LightsEditor::LightsEditor()
{
    currentLight = 0;
    currentTree = 0;
    circleRadius = 7.0f;
    ofAddListener(ofEvents().mousePressed, this, &LightsEditor::mousePressed);
//	ofAddListener(ofEvents().mouseMoved, this, &LightsEditor::mouseMoved);
    ofAddListener(ofEvents().mouseDragged, this, &LightsEditor::mouseDragged);
//	ofAddListener(ofEvents().mouseReleased, this, &LightsEditor::mouseReleased);
    ofAddListener(ofEvents().keyPressed, this, &LightsEditor::keyPressed);
}

LightsEditor::~LightsEditor()
{
    //dtor
}

void LightsEditor::setup()
{

}

void LightsEditor::load(vector<Tree *> * _trees)
{
    trees = _trees;
    string name = trees->at(currentTree)->getName();
    treeimg.load("TreePhotos/"+name+" wires.jpg");
    treeimg.setImageType(OF_IMAGE_GRAYSCALE);
}

void LightsEditor::draw()
{
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    treeimg.draw(ofGetWidth()/2,ofGetHeight()/2,1280,960);

    for(int j=0; j < trees->at(currentTree)->lights.size();j++)
    {
        /* Draw circle */
        ofVec2f pos = trees->at(currentTree)->lights.at(j)->getPosition();
        ofNoFill();
        if(currentLight == j) {
            ofSetColor(255,0,0);
        }
        else {
            ofSetColor(0,0,255);
        }
        ofDrawCircle(pos,circleRadius);

        /* Draw LEDs */
        for(int k=0; k < trees->at(currentTree)->lights.at(j)->pixels.size(); k++)
        {
            ofColor c = trees->at(currentTree)->lights.at(j)->pixels[k]->getColour();
            float b = trees->at(currentTree)->lights.at(j)->pixels[k]->getBrightness();
            ofSetColor(c.r * b, c.g * b, c.b * b);
            ofFill();
            ofDrawRectangle(pos,3,3);
            pos.y += 4.0f;
        }
    }

    ofSetColor(255);
    ofDrawBitmapString("Name = " + trees->at(currentTree)->getName()+" Tree = "+ofToString(currentTree)+"  Light Id= "+ofToString(currentLight) ,20,ofGetHeight()-20);

    ofPopStyle();
}

void LightsEditor::keyPressed(ofKeyEventArgs& args)
{

    if(args.key == OF_KEY_LEFT) {
        currentLight--;
        if(currentLight < 0) currentLight = trees->at(currentTree)->lights.size()-1;
    }

    if(args.key == OF_KEY_RIGHT) {
        currentLight++;
        if(currentLight >= (trees->at(currentTree)->lights.size())) currentLight = 0;
    }

    if(args.key == '[') {
        currentTree--;
        if(currentTree < 0) currentTree = trees->size() -1;
        string name = trees->at(currentTree)->getName();
        treeimg.load("TreePhotos/"+name+" wires.jpg");
        treeimg.setImageType(OF_IMAGE_GRAYSCALE);
    }

    if(args.key == ']') {
        currentTree++;
        if(currentTree >= trees->size()) currentTree = 0;
        string name = trees->at(currentTree)->getName();
        treeimg.load("TreePhotos/"+name+" wires.jpg");
        treeimg.setImageType(OF_IMAGE_GRAYSCALE);
    }
}

void LightsEditor::mousePressed(ofMouseEventArgs& args)
{
    float distance = 10000;
    int id = 0;
    ofVec2f p = ofVec2f(args.x,args.y);
    for(int j=0; j < trees->at(currentTree)->lights.size();j++)
    {
        ofVec2f pos = trees->at(currentTree)->lights.at(j)->getPosition();
        float dist = p.distance(pos);
        if(dist < distance ) {
            distance = dist;
            id = j;
        }

    }
    if(distance < circleRadius/2) {
        currentLight = id;
    } else {
        trees->at(currentTree)->lights[currentLight]->setPosition(ofVec2f(args.x, args.y));
    }
}

void LightsEditor::mouseDragged(ofMouseEventArgs& args)
{
    trees->at(currentTree)->lights.at(currentLight)->setPosition(ofVec2f(args.x,args.y));

}
