#include "DataHandle.h"
#include "tinyxml2.h"
using namespace tinyxml2;


DataHandle::DataHandle()
{
}


DataHandle::~DataHandle()
{
}

vector<Box*> DataHandle::ReadData()
{
	m_vBoxes.reserve(4);
	//read file

	XMLDocument xmlDoc;

	xmlDoc.LoadFile("rec.xml");
	XMLNode* pRoot = xmlDoc.FirstChildElement("root");

	XMLElement* pElement = pRoot->FirstChildElement("Box");
	int x, y;
	unsigned int  r, g, b;
	while (pElement != nullptr)
	{
		pElement->QueryIntAttribute("x", &x);
		pElement->QueryIntAttribute("y", &y);
		pElement->QueryUnsignedAttribute("r", &r);
		pElement->QueryUnsignedAttribute("g", &g);
		pElement->QueryUnsignedAttribute("b", &b);

		m_vBoxes.push_back(new Box({ x, y, 100, 100 }, { (Uint8)r,(Uint8)g,(Uint8)b,255 }));
		pElement = pElement->NextSiblingElement("Box");
	}

	return m_vBoxes;
}

void DataHandle::WriteData(vector<Box*> vBoxes)
{
	XMLDocument xmlDoc;
	xmlDoc.LoadFile("rec.xml");
	XMLNode* pRoot = xmlDoc.FirstChildElement("root");

	XMLElement* pElement = pRoot->FirstChildElement("Box");
	Uint8 x, y, r, g, b;
	int i = 0;
	while (pElement != nullptr)
	{

		pElement->SetAttribute("x", vBoxes[i]->getBoxSize().x);
		pElement->SetAttribute("y", vBoxes[i]->getBoxSize().y);
		pElement->SetAttribute("r", vBoxes[i]->getBoxColor().r);
		pElement->SetAttribute("g", vBoxes[i]->getBoxColor().g);
		pElement->SetAttribute("b", vBoxes[i]->getBoxColor().b);


		pElement = pElement->NextSiblingElement("Box");
		i++;
	}
	xmlDoc.SaveFile("rec.xml");

}
