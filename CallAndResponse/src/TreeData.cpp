#include "TreeData.h"
#include "Tree.h"
#include "LedFixture.h"

TreeData::TreeData()
: state(LIGHTS_ON),
  bIsPlaying(true),
  bShowBgImage(true),
  currentTree(0),
  currentLight(0),
  nextTree(0),
  targetTree(0),
  direction(1),
  colour(ofColor::black),
  brightness(1.0f),
  pixelWidth(1.0f)
{
    currentTree = 8;
    pixelWidth = 6.0f;

    parameters.setName("parameters");
    parameters.add(bIsPlaying.set("Playing",true));
}

TreeData::~TreeData()
{

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


