#include "TreeMesh.h"

TreeMesh::TreeMesh()
{
    //ctor
}

//--------------------------------------------------------------
TreeMesh::~TreeMesh()
{
    //dtor
}

void TreeMesh::setTransform(ofMatrix4x4& mat)
{
    node.setTransformMatrix(mat);
}

//--------------------------------------------------------------
void TreeMesh::setMesh(ofMesh& _mesh) {
    mesh = _mesh;
}

//--------------------------------------------------------------
void TreeMesh::draw()
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
