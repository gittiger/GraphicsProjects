#pragma once
#include <string>
#include <list>
#include "image.h"
#include "rapidxml_utils.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace rapidxml;

class Action
{
private:
	string m_actionName;
	list<Image *> moves;
	Image *m_currentImage;
	list <Image *> ::iterator itImage;

public:
	Action(string xmlActions);
	string getActionName() const;
	Image *getCurrentImage() const;
	void run();
	void next();
	void prev();
	void restart();
};