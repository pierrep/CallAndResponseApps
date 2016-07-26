#include "LineEffect.h"

LineEffect::LineEffect()
{
    name = "Line";
    parameters.setName(name + baseName);
    parameters.add(numLines.set("Number of lines",5,1,20));
    parameters.add(lineWidth.set("Line width",2,1,10));
    parameters.add(lineSpeed.set("Line speed",2.0f,1.0f,10.0f));
    numLines.addListener(this,&LineEffect::onLinesChanged);
}

LineEffect::~LineEffect()
{

}

void LineEffect::setup()
{
    resetLines();
}

void LineEffect::begin()
{
    if(!bEnabled) return;
    data->bUseFrameBuffer = true;

    resetLines();
}

void LineEffect::update(float curTime)
{
    if(!bEnabled) return;

    BaseEffect::update(curTime);

    for(int i = 0;i < lines.size();i++) {
        lines[i].p1.y -= lineSpeed.get();
        lines[i].p2.y -= lineSpeed.get();

        lines[i].p1.x = curTime*1200;
        lines[i].p2.x = lines[i].p1.x + 400;

        if(lines[i].p1.y < 0)
            lines[i].p1.y = ofGetHeight();

        if(lines[i].p2.y < 0)
            lines[i].p2.y = ofGetHeight();
    }

}

void LineEffect::draw(float x, float y, float w, float h)
{
    if(!bEnabled) return;

    ofPushStyle();
    ofSetColor(255,0,255.0f);
    ofSetLineWidth(lineWidth.get());
    for(int i = 0;i < lines.size();i++) {
        ofDrawLine(lines[i].p1,lines[i].p2);
    }

    ofPopStyle();
}

void LineEffect::resetLines()
{
    lines.clear();
    for(int i=0;i < numLines.get();i++)
    {
        float interval = 900 / numLines.get();
        ofVec2f p1 = ofVec2f(0,(i)*interval);
        ofVec2f p2 = ofVec2f(ofGetWidth(),(i)*interval);
        Line line;
        line.p1 = p1;
        line.p2 = p2;
        lines.push_back(line);
    }
}

void LineEffect::onLinesChanged(int & n)
{
    resetLines();
}
