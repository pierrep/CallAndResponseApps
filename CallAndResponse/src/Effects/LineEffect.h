#pragma once

#include "ofMain.h"
#include "BaseEffect.h"

class LineEffect : public BaseEffect
{
    public:

        LineEffect();
        ~LineEffect();

        void update(float time);
        void draw(float x, float y, float w, float h);
        void setup();
        void begin();
        void onLinesChanged(int &n);
        void resetLines();

        struct Line {
            ofVec2f p1;
            ofVec2f p2;
        };
        vector<Line>     lines;
        ofParameter<int>    numLines;
        ofParameter<int>    lineThickness;
        ofParameter<int>    lineWidth;
        ofParameter<float>  lineVerticalSpeed;
        ofParameter<float>  lineHorizontalSpeed;

        ofImage* curImage;
};
