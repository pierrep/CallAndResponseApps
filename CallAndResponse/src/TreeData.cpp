#include "TreeData.h"


TreeData::TreeData()
{
    //ctor
}

TreeData::~TreeData()
{
    //dtor
}

void TreeData::load(vector<Tree *>& trees)
{
    xml.load("TreeData.xml");
    xml.pushTag("Trees");

    int numTrees = xml.getNumTags("Tree");

    for(int t = 0; t < numTrees; t++)
    {
        xml.pushTag("Tree", t);
        int treeId = xml.getValue("TreeId",-1);
        string name = xml.getValue("TreeName","none");
        Tree* tree = new Tree();
        tree->setId(treeId);
        tree->setName(name);

        int numLights = xml.getNumTags("Light");

        for(int i = 0; i < numLights; i++)
        {
            int id = xml.getValue("Light:id", 0, i);
            int x = xml.getValue("Light:x", 0, i);
            int y = xml.getValue("Light:y", 0, i);

            LedFixture* led = new LedFixture();
            led->setId(id);
            led->setPosition(ofVec2f(x,y));
            led->setupPixels();
            tree->lights.push_back(led);
        }

        trees.push_back(tree);
        xml.popTag();
    }
    xml.popTag();

}


void TreeData::save(vector<Tree *>& trees)
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


