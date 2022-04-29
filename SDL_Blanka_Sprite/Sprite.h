#pragma once
#include "Action.h"

class Sprite
{
protected:
	std::list<Action*> m_actions;
	Action* m_currentAction;
	string m_name;
	int m_W;
	int m_H;
	int m_X;
	int m_Y;

private:
	void loadSprite(string xmlSprite);

public:
	Sprite(string xmlSprite);
	~Sprite();
	void addAction(Action* act);
	void removeAction(Action* act);
	Action* getCurrentAction() const;
	virtual void executeAction(string actionName) = 0;
};
