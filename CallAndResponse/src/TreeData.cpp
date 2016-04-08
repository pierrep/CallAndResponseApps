#include "TreeData.h"


TreeData::TreeData()
{
   currentTree = 5;
   currentLight = 0;
   isPlaying = true;
   bShowBgImage = true;
   pixelWidth = 6.0f;
   state = LIGHTS_ON;
}

TreeData::~TreeData()
{
    //dtor
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

        Tree* tree = new Tree();
        tree->setId(treeId);
        tree->setName(name);
        tree->setMapPos(ofVec2f(Mapx,Mapy));

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


