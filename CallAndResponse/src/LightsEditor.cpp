#include "LightsEditor.h"


LightsEditor::LightsEditor()
{
    currentLight = 0;
    circleRadius = 8.0f;
    pixelRadius = 4.0f;

    editorWidth = 1200;
    editorHeight = 900;
    disableEditing();

}

LightsEditor::~LightsEditor()
{
    //dtor
}

void LightsEditor::setup(TreeData* _data)
{
    data = _data;

    for(int i=0; i < data->trees.size();i++) {
        string name = data->trees.at(i)->getName();
        ofImage img;
        img.load("TreePhotos/"+name+".jpg");
        img.setImageType(OF_IMAGE_GRAYSCALE);
        treeimg.push_back(img);
    }

    lightNum.load("Gotham-Thin.otf",11,true);

}

void LightsEditor::draw()
{
    draw(0,0,editorWidth,editorHeight);
}

void LightsEditor::draw(float x, float y, float w, float h)
{
    ofPushMatrix();
    ofTranslate(x,y,0);
    ofPushStyle();
    //ofClear(255,255,255, 0);
    if(data->bShowBgImage) {
        treeimg[data->currentTree].draw(0,0,editorWidth,editorHeight);
    }

    ofSetRectMode(OF_RECTMODE_CENTER);
    unsigned int numLights = data->trees[data->currentTree]->lights.size();
    for(int j=0; j < numLights;j++)
    {
        /* Draw circle */
        ofVec2f pos = data->trees[data->currentTree]->lights.at(j)->getPosition();
        ofNoFill();
        ofSetLineWidth(3);
        if(currentLight == j) {
            ofSetColor(0,0,255);
        }
        else {
            ofSetColor(100,100,100);
        }
        ofDrawCircle(pos,circleRadius);

        ofSetHexColor(0xff3355);
        float w = 10.0f + lightNum.stringWidth(ofToString(j+1));
        lightNum.drawString(ofToString(j+1),pos.x - w,pos.y + circleRadius);

        ofSetColor(100,100,100);
        ofSetLineWidth(1);
        if(j+1 < numLights-1) {
            ofVec2f pos2 = data->trees[data->currentTree]->lights.at(j+1)->getPosition();
            ofDrawLine(pos.x,pos.y,pos2.x,pos2.y);
        }

        /* Draw LEDs */
        for(int k=0; k < data->trees[data->currentTree]->lights.at(j)->pixels.size(); k++)
        {
            ofColor c = data->trees[data->currentTree]->lights.at(j)->pixels[k]->getColour();
            float b = data->trees[data->currentTree]->lights.at(j)->pixels[k]->getBrightness();
            ofSetColor(c.r * b, c.g * b, c.b * b);
            ofFill();
            ofDrawRectangle(pos,pixelRadius,pixelRadius);
            pos.y += pixelRadius+1;
        }
    }

    ofSetColor(255);
    ofDrawBitmapString("Name = " + data->trees[data->currentTree]->getName()+" Tree = "+ofToString(data->currentTree)+"  Light Id= "+ofToString(currentLight) ,20,ofGetHeight()-20);

    ofPopStyle();
    ofPopMatrix();

}

void LightsEditor::keyPressed(ofKeyEventArgs& args)
{

    if(args.key == OF_KEY_LEFT) {
        currentLight--;
        if(currentLight < 0) currentLight = data->trees[data->currentTree]->lights.size()-1;
    }

    if(args.key == OF_KEY_RIGHT) {
        currentLight++;
        if(currentLight >= (data->trees[data->currentTree]->lights.size())) currentLight = 0;
    }

    if(args.key == '[') {
        data->currentTree--;
        if((data->currentTree < 0) || (data->currentTree >= data->trees.size())) data->currentTree = data->trees.size()-1;
    }

    if(args.key == ']') {
        data->currentTree++;
        if(data->currentTree >= data->trees.size()) data->currentTree = 0;
    }
}

void LightsEditor::mousePressed(ofMouseEventArgs& args)
{
    float distance = 10000;
    int id = 0;
    ofVec2f p = ofVec2f(args.x-400,args.y);
    for(int j=0; j < data->trees[data->currentTree]->lights.size();j++)
    {
        ofVec2f pos = data->trees[data->currentTree]->lights.at(j)->getPosition();
        float dist = p.distance(pos);
        if(dist < distance ) {
            distance = dist;
            id = j;
        }

    }
    if(distance < circleRadius/2) {
        currentLight = id;
    } else {
        data->trees[data->currentTree]->lights[currentLight]->setPosition(ofVec2f(args.x-400, args.y)); //ofMap(args.x,400,1600,0,1600)
    }
}

void LightsEditor::mouseDragged(ofMouseEventArgs& args)
{
    data->trees[data->currentTree]->lights.at(currentLight)->setPosition(ofVec2f(args.x-400, args.y));

}

void LightsEditor::mouseMoved(ofMouseEventArgs& args) {

}

void LightsEditor::mouseReleased(ofMouseEventArgs& args) {

}


void LightsEditor::enableEditing() {
    ofAddListener(ofEvents().mousePressed, this, &LightsEditor::mousePressed);
    ofAddListener(ofEvents().mouseMoved, this, &LightsEditor::mouseMoved);
    ofAddListener(ofEvents().mouseDragged, this, &LightsEditor::mouseDragged);
    ofAddListener(ofEvents().mouseReleased, this, &LightsEditor::mouseReleased);

    ofAddListener(ofEvents().keyPressed, this, &LightsEditor::keyPressed);
    //ofAddListener(ofEvents().keyReleased, this, &LightsEditor::keyReleased);
}

void LightsEditor::disableEditing() {
    ofRemoveListener(ofEvents().mousePressed, this, &LightsEditor::mousePressed);
    ofRemoveListener(ofEvents().mouseMoved, this, &LightsEditor::mouseMoved);
    ofRemoveListener(ofEvents().mouseDragged, this, &LightsEditor::mouseDragged);
    ofRemoveListener(ofEvents().mouseReleased, this, &LightsEditor::mouseReleased);

    ofRemoveListener(ofEvents().keyPressed, this, &LightsEditor::keyPressed);
    //ofRemoveListener(ofEvents().keyReleased, this, &LightsEditor::keyReleased);

}
