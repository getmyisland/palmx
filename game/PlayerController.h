#ifndef PLAYER_CONTROLLER_H_
#define PLAYER_CONTROLLER_H_

#include <entity/Entity.h>
#include <entity/ScriptBehavior.h>

class PlayerController : public palmx::ScriptBehavior
{
public:
	void Update(palmx::EntityID entityId, float deltaTime) override;

private:
	float _movementSpeed = 3.5f;
	float _mouseSensitivity = 0.1f;
};

#endif