#include "LedFixture.h"

LedFixture::LedFixture()
{
    //ctor
}

//--------------------------------------------------------------
LedFixture::~LedFixture()
{
    //dtor
}

void LedFixture::setupPixels()
{
    for(int i=0; i < NUM_PIXELS_PER_FIXTURE; i++) {
        LedPixel* p = new LedPixel();
        p->setId((id -1)*NUM_PIXELS_PER_FIXTURE + i);
        pixels.push_back(p);
    }
}

//--------------------------------------------------------------
void LedFixture::setMesh(ofMesh& _mesh) {
    mesh = _mesh;
}

//--------------------------------------------------------------
void LedFixture::setColour(ofColor c)
{
    for(int i = 0;i < pixels.size();i++)
    {
        pixels[i]->setColour(c);
    }
}

//--------------------------------------------------------------
void LedFixture::setBrightness(float val)
{
    for(int i = 0;i < pixels.size();i++)
    {
        pixels[i]->setBrightness(val);
    }
}

//--------------------------------------------------------------
void LedFixture::fadeOn()
{
    for(int i = 0;i < pixels.size();i++)
    {
        pixels[i]->fadeOn(i);
    }
}

//--------------------------------------------------------------
void LedFixture::update()
{
    for(int i = 0;i < pixels.size();i++)
    {
        pixels[i]->update();
    }

}

//--------------------------------------------------------------
void LedFixture::draw()
{
    ofPushStyle();
    ofSetColor(0,0,255);

	ofEnableDepthTest();

    ofPushMatrix();
        ofMultMatrix(getLocalTransformMatrix());
        //model.drawWireframe();
        mesh.drawWireframe();
        ofVec3f c = mesh.getCentroid();
        ofDrawSphere(c.x,c.y,c.z,0.05f);
        //mesh.getVertices();
//        for(int i = 0 ; i < mesh.getNumVertices();i++) {
//          ofVec3f v = mesh.getVertices().at(i);
//        }
    ofPopMatrix();


    ofDisableDepthTest();
    ofPopStyle();
}
