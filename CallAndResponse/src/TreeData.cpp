#include "TreeData.h"
#include "LedFixture.h"

TreeData::TreeData()
: state(LIGHTS_ON),
  lastState(LIGHTS_ON),
  bIsPlaying(true),
  bShowBgImage(true),
  bEditMode(false),
  direction(1),
  colour(ofColor::black),
  pixelWidth(6.0f),
  bUseFrameBuffer(true)
{
    currentTree = 8;
	tree2 = -1;
	tree3 = -1;
	tree4 = -1;

    float master_brightness = 0.4f;

    if(ofGetMonth() == 10 || ofGetMonth() == 11 || ofGetMonth() == 12 || ofGetMonth() == 1 || ofGetMonth() == 2)
    {
        master_brightness = 0.7f;
    } else {
        master_brightness = 0.40f;
    }

    parameters.setName("parameters");
    parameters.add(brightness.set("Brightness",master_brightness,0.0f,1.0f));
    parameters.add(bTogglePlaying.set("Playing (spacebar)",true));
    parameters.add(bShowBgImage.set("Show Background (i)",true));
    parameters.add(bToggleEditMode.set("Edit Mode (e)",false));
    parameters.add(bBeginAnimation.set("Begin Animation (b)",false));
    parameters.add(bNextAnimation.set("Next Animation (n)",false));
    parameters.add(currentTree.set("Current Tree",0,0,16));
    parameters.add(currentLight.set("Current Light",0,0,19));
    parameters.add(nextTree.set("Next Tree",0,0,16));
    parameters.add(targetTree.set("Target Tree",0,0,16));
    parameters.add(lightPosition.set("Light Position",ofVec2f(400,0), ofVec2f(400,0), ofVec2f(1600,900)));
    parameters.add(mousePosition.set("Mouse Position",ofVec2f(400,0), ofVec2f(400,0), ofVec2f(1600,900)));
    parameters.add(tree2.set("Tree2",0,0,16));
    parameters.add(tree3.set("Tree3",0,0,16));
    parameters.add(tree4.set("Tree4",0,0,16));
    parameters.add(animationType.set("Animation Type",0,0,5));
    parameters.add(bChangeAnimation.set("Change Animation",false));
    parameters.add(bMoveForward.set("Forward",false));
    parameters.add(bMoveBack.set("Back",false));
    parameters.add(colour.set("Colour",ofColor(0,255,0)));
    lightPosition.addListener(this, &TreeData::lightPositionChanged);

    currentPaletteImage = 0;
    numPaletteImgs = 0;
    ofDirectory dir("Images/");
    dir.sort();
    size_t numFiles = dir.listDir();

    for(size_t i = 0; i < numFiles; i++) {
        ofImage tmpImg;
        tmpImg.load("Images/palette"+ofToString(i)+".png");
        if(((int)tmpImg.getWidth() != 1200) || ((int)tmpImg.getHeight() != 900)) {
            ofLogError() << "Incorrect palette image size " << tmpImg.getWidth() <<"x" << tmpImg.getHeight() << ", skipping image " << "Images/palette"+ofToString(i)+".png";
        } else {
            paletteImage.push_back(tmpImg);
            numPaletteImgs++;
        }

    }
    ofLogNotice() << " Number of palette images = " << numPaletteImgs;
    if(numPaletteImgs == 0) {
        ofLogError() << "Couldn't find any palette images, exiting";
        ofExit();
    }
}

//--------------------------------------------------------------
TreeData::~TreeData()
{
    lightPosition.removeListener(this,&TreeData::lightPositionChanged);

    for (vector< Tree *>::iterator itr = trees.begin() ; itr != trees.end(); ++itr)
    {
        // delete the lights
        for (vector< LedFixture *>::iterator itr2 = (*itr)->lights.begin() ; itr2 != (*itr)->lights.end(); ++itr2)
        {
            delete (*itr2);
        }
        (*itr)->lights.clear();

        //delete the tree
        delete (*itr);
    }
    trees.clear();


}

//--------------------------------------------------------------
void TreeData::lightPositionChanged(ofVec2f & lightPosition){

    trees[currentTree]->lights[currentLight]->setPosition(lightPosition);
}

//--------------------------------------------------------------
ofColor TreeData::getRandomPaletteColour()
{
    int  x = (int) ofRandom(0,paletteImage[currentPaletteImage].getWidth());
    int  y = (int) ofRandom(0,paletteImage[currentPaletteImage].getHeight());
    ofColor c = paletteImage[currentPaletteImage].getColor(x,y);
    return c;
}

//--------------------------------------------------------------
ofColor TreeData::getRandomPaletteColourX(int y)
{
    int  x = (int) ofRandom(0,paletteImage[currentPaletteImage].getWidth());
    ofColor c = paletteImage[currentPaletteImage].getColor(x,y);
    return c;
}

//--------------------------------------------------------------
ofColor TreeData::setSimilarPaletteColour(ofColor c, float offset)
{
    float value = (c.r + c.g + c.b)/3.0f;
    float newValue = value + (ofRandomf() * offset);
    float valueRatio = newValue / value;

    ofColor newColour;
    newColour.r = static_cast<unsigned char>(c.r * valueRatio);
    newColour.g = static_cast<unsigned char>(c.g * valueRatio);
    newColour.b = static_cast<unsigned char>(c.b * valueRatio);
    return newColour;
}

//--------------------------------------------------------------
ofColor TreeData::setSimilarPaletteColourHSB(ofColor c, float offset)
{
    float h,s,b;
    c.getHsb(h,s,b);

    float hue = h + (ofRandomf() * offset);
    hue = ofClamp(hue,0,255);

    ofColor newColour;
    newColour.setHsb(hue,255,b);
    return newColour;
}

//--------------------------------------------------------------
void TreeData::load()
{
    xml.load("TreeData.xml");
    xml.pushTag("Trees");

    int numTrees = xml.getNumTags("Tree");

    for(int t = 0; t < numTrees; t++)
    {
        xml.pushTag("Tree", t);
        int treeId = xml.getValue("TreeId",0);
        string name = xml.getValue("TreeName","none");
        int Mapx = xml.getValue("MapPosX",-1);
        int Mapy = xml.getValue("MapPosY",-1);
        int vol = xml.getValue("Volume",2);

        Tree* tree = new Tree();
        tree->setId(treeId);
        tree->setName(name);
        tree->setMapPos(ofVec2f(Mapx,Mapy));
        tree->setVolume(vol);

        int numLights = xml.getNumTags("Light");

        for(int i = 0; i < numLights; i++)
        {
            int id = xml.getValue("Light:id", 0, i);
            int x = xml.getValue("Light:x", 0, i);
            int y = xml.getValue("Light:y", 0, i);

            LedFixture* led = new LedFixture();
            led->setId(id);
            led->setPosition(ofVec2f(x,y));
            led->setupPixels(ofVec2f(x,y),pixelWidth);
            tree->lights.push_back(led);
        }

        trees.push_back(tree);
        xml.popTag();
    }
    xml.popTag();

}

//--------------------------------------------------------------
void TreeData::save()
{
    xml.clear();
    xml.addTag("Trees");
    xml.pushTag("Trees");



    for(int t = 0; t < trees.size(); t++)
    {
        xml.addTag("Tree");
        xml.pushTag("Tree",t);

        xml.addValue("TreeId", trees[t]->getId());
        xml.addValue("TreeName", trees[t]->getName());
        xml.addValue("MapPosX", trees[t]->getMapPos().x);
        xml.addValue("MapPosY", trees[t]->getMapPos().y);
        xml.addValue("Volume", trees[t]->getVolume());

        for(int i = 0; i < trees[t]->lights.size(); i++)
        {
            int tagnum = xml.addTag("Light");
            xml.pushTag("Light",tagnum);

            xml.addValue("id", trees[t]->lights[i]->getId());
            xml.addValue("x", trees[t]->lights[i]->getPosition().x);
            xml.addValue("y", trees[t]->lights[i]->getPosition().y);

            xml.popTag();
        }

        xml.popTag();
    }

   xml.save("TreeData.xml");
}


