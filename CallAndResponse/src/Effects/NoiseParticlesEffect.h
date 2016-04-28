#pragma once

#define MAX_PARTICLES 5000

#include "ofMain.h"
#include "BaseEffect.h"

class NoiseParticle;

class NoiseParticlesEffect : public BaseEffect
{
    public:

        NoiseParticlesEffect();
        ~NoiseParticlesEffect();

        void update(float time);
        void draw(float x, float y, float w, float h);        
        void setup();
        void begin();
        void drawFlowfield();

        vector<NoiseParticle> flow;       

        float globalX, globalY;
        float posArray[MAX_PARTICLES * 2 * 2];
        float colArray[MAX_PARTICLES * 3 * 2];
        int curIndex;

};

// a basic noise-based moving particle
class NoiseParticle
{
  float id;
  float x, y, xp, yp;
  float speed;
  float dir;
  ofFloatColor colorPalette[4];

public:
  NoiseParticle(float _id) {
    id = _id;
    x = y = 256;
    speed = ofRandom(2, 6);


    colorPalette[0] = ofColor(254,150,51,255);
    colorPalette[1] = ofColor(139,225,226,255);
    colorPalette[2] = ofColor(255,229,155,255);
    colorPalette[3] = ofColor(0,189,151,255);

  }

  void reset()
  {
      x = y = xp = yp = 0;
  }

  void update(float globalX, float globalY, float kinectWidth, float kinectHeight) {
    // let it flow, end with a new x and y position
    id += 0.01f;
    dir = (ofNoise(id, x/globalY, y/globalY)-0.5)*globalX;
    float angle = ofDegToRad(dir);
    x += 1.0f + cos(angle)*speed;
    y += sin(angle)*speed;

    // constrain to boundaries
    if (x<-10) x=xp=kinectWidth+10; if (x>kinectWidth+10) x=xp=-10;
    if (y<-10) y=yp=kinectHeight+10; if (y>kinectHeight+10) y=yp=-10;

    //ofLine(xp, yp, x, y); // line from previous to current position

  }

void updateVertexArrays( float w, float h, int i, float* posBuffer, float* colBuffer) {
    int vi = i * 4;
    posBuffer[vi++] = xp;
    posBuffer[vi++] = yp;
    posBuffer[vi++] = x;
    posBuffer[vi++] = y;

    // set previous to current position
    xp=x;
    yp=y;

    int ci = i * 6;

    ofFloatColor color = colorPalette[i%4];

    colBuffer[ci++] = color.r;
    colBuffer[ci++] = color.g;
    colBuffer[ci++] = color.b;
    colBuffer[ci++] = color.r;
    colBuffer[ci++] = color.g;
    colBuffer[ci++] = color.b;
}

};
