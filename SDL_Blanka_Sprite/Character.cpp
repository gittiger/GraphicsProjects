#include "Character.h"

Character::Character(string xmlSprite)
    : Sprite(xmlSprite)
{
}

void Character::executeAction(string actionName)
{
	std::list<Action*>::iterator it;

    it = std::find_if(m_actions.begin(), m_actions.end(), [&](Action *action){ return action->getActionName().compare(actionName) == 0; });
    if (it != m_actions.end())
    {
        m_currentAction = *it;      
    }
    else
    {
        m_currentAction = NULL;
    }
}