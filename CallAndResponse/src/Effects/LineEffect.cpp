#include "LineEffect.h"

LineEffect::LineEffect()
{
    name = "Line";
    parameters.setName(name + baseName);
    parameters.add(numLines.set("Number of lines",5,1,20));
    parameters.add(lineThickness.set("Line thickness",40,10,100));
    parameters.add(lineWidth.set("Line width",1200,100,1600));
    parameters.add(lineVerticalSpeed.set("Line vertical speed",2.0f,1.0f,10.0f));
    parameters.add(lineHorizontalSpeed.set("Line horizontal speed",1200,100,1600));
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
        lines[i].p1.y -= lineVerticalSpeed.get();
        lines[i].p1.x = curTime*lineHorizontalSpeed.get();

        if(lines[i].p1.y < 0)
            lines[i].p1.y = ofGetHeight();
    }

}

void LineEffect::draw(float x, float y, float w, float h)
{
    if(!bEnabled) return;

    ofPushStyle();
    ofSetColor(255,0,255.0f);

    for(unsigned int i = 0;i < lines.size();i++)
    {
        ofMesh temp;
        temp.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        temp.addVertex( lines[i].p1 );
        temp.addColor(ofColor(255,0,255));
        temp.addVertex( ofPoint(lines[i].p1.x+lineWidth.get(),lines[i].p1.y) );
        temp.addColor(ofColor(255,0,255));
        temp.addVertex( ofPoint(lines[i].p1.x,lines[i].p1.y+lineThickness.get()) );
        temp.addColor(ofColor::black);
        temp.addVertex( ofPoint(lines[i].p1.x+lineWidth.get(),lines[i].p1.y+lineThickness.get()) );
        temp.addColor(ofColor::black);
        temp.draw();
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
        Line line;
        line.p1 = p1;
        lines.push_back(line);
    }
}

void LineEffect::onLinesChanged(int & n)
{
    resetLines();
}
