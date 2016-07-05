#include "LedFixture.h"

LedFixture::LedFixture()
{
    id = 0;
    pos = ofVec2f::zero();
}

//--------------------------------------------------------------
LedFixture::~LedFixture()
{
    for (std::vector< LedPixel *>::iterator itr = pixels.begin() ; itr != pixels.end(); ++itr)
    {
      delete (*itr);
    }
    pixels.clear();
}

void LedFixture::setupPixels(ofVec2f pos, float pixelWidth)
{
    for(int i=0; i < NUM_PIXELS_PER_FIXTURE; i++) {
        LedPixel* p = new LedPixel();
        p->setId((id -1)*NUM_PIXELS_PER_FIXTURE + i);
        float y = pos.y + i*(pixelWidth+1);
        ofVec2f v = ofVec2f(pos.x , y);
        p->setPosition(v);
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
