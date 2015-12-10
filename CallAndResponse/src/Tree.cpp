#include "Tree.h"

Tree::Tree()
{
    memset(buf, 0, 512*sizeof(unsigned char));
}

//--------------------------------------------------------------
Tree::~Tree()
{
    //dtor
}

//--------------------------------------------------------------
void Tree::clear()
{
    memset(buf, 0, 512*sizeof(unsigned char));
    for(int i = 0; i < lights.size();i++)
    {
        lights[i].setColour(ofColor::black);
        lights[i].setBrightness(0.0f);
    }
}

//--------------------------------------------------------------
void Tree::setTransform(ofMatrix4x4& mat)
{
    node.setTransformMatrix(mat);
}

//--------------------------------------------------------------
void Tree::setMesh(ofMesh& _mesh) {
    mesh = _mesh;
}

//--------------------------------------------------------------
void Tree::update()
{
    int bufindex = 0;
    for(int i=0; i < lights.size();i++)
    {
        for(int j=0; j < lights[i].pixels.size();j++) {
            for(int k = 0; k < 3; k++) {
                buf[bufindex] = lights[i].pixels[j].getDMXValue(k);
                bufindex++;
            }
        }

    }

}

//--------------------------------------------------------------
void Tree::draw()
{
    ofSetColor(0);

    ofEnableDepthTest();

    ofPushMatrix();
        ofMultMatrix(node.getLocalTransformMatrix());
        //model.drawWireframe();
        mesh.drawWireframe();
        ofVec3f c = mesh.getCentroid();
        ofSetColor(0,0,255);
        //ofSphere(c.x,c.y,c.z,1);
        //mesh.getVertices();
//        for(int i = 0 ; i < mesh.getNumVertices();i++) {
//          ofVec3f v = mesh.getVertices().at(i);
//        }
    ofPopMatrix();


    ofDisableDepthTest();

}
