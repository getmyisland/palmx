#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include <entity/components/ScriptBehavior.h>

class PlayerController : public PalmEngine::ScriptBehavior
{
public:
	virtual void Update() override;
};

#endif