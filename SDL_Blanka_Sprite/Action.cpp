#include "Action.h"

Action::Action(string xmlActions)
{
	rapidxml::file<> xmlFile(xmlActions.c_str()); 
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	xml_node<>* pRoot = doc.first_node();
	m_actionName = pRoot->first_attribute("name")->value();

	for (xml_node<>* pNode = pRoot->first_node("Image"); pNode; pNode = pNode->next_sibling())
	{
		string image_name = pNode->value();
		string imgPath = pRoot->first_attribute("path")->value();
		Image *newImage = new Image(imgPath + image_name);
		moves.push_back(newImage);
	}
}

string Action::getActionName() const
{
	return m_actionName;
}

Image *Action::getCurrentImage() const
{
	return m_currentImage;
}

void Action::run()
{
	itImage = moves.begin();
	m_currentImage = *itImage;
}

void Action::next()
{
	if (itImage != moves.end())
		itImage++;
}

void Action::prev()
{
	if(itImage != moves.begin())
		itImage--;
}

void Action::restart()
{
	run();
}