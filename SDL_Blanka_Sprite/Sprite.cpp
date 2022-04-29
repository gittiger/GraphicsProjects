#include "Sprite.h"

Sprite::Sprite(string xmlSprite)
{
	loadSprite(xmlSprite);
}

Sprite::~Sprite()
{
	if (m_actions.size() > 0)
	{
		list<Action*>::iterator it;
		for (m_actions.begin(); it != m_actions.end(); it++)
		{
			Action* temp = *it;
			delete temp;
		}
	}
}

void Sprite::loadSprite(string xmlSprite)
{
	rapidxml::file<> xmlFile(xmlSprite.c_str());
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	xml_node<>* pRoot = doc.first_node();
	m_name = pRoot->first_attribute("name")->value();
	for (xml_node<>* pNode = pRoot->first_node("Action"); pNode; pNode = pNode->next_sibling())
	{
		string actionXml = pNode->value();
		string folderPath = pRoot->first_attribute("folder")->value();
		Action* tempAct = new Action(folderPath + actionXml);
		tempAct->run();
		m_actions.push_back(tempAct);
	}
}

void Sprite::addAction(Action* act)
{
	m_actions.push_back(act);
}

void Sprite::removeAction(Action* act)
{
	m_actions.remove(act);
}

Action* Sprite::getCurrentAction() const
{
	return m_currentAction;
}