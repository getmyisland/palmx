#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include <entity/Entity.h>

class PlayerController : public PalmEngine::ScriptBehavior
{
public:
	void Update(float deltaTime, PalmEngine::Transform& transform) override;

private:
	float _movementSpeed = 2.5f;
};

#endif