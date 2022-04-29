#pragma once
#include "Sprite.h"

class Character : public Sprite
{
public:
	Character(string xmlSprite);
	void executeAction(string actionName);
};
