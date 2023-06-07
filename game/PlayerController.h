#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include <scene/components/ScriptBehavior.h>
#include <scene/Entity.h>

class PlayerController : public PalmEngine::ScriptBehavior
{
public:
	void Update(PalmEngine::EntityID entityID, float deltaTime) override;

private:
	float _movementSpeed = 3.5f;
	float _mouseSensitivity = 0.1f;
};

#endif