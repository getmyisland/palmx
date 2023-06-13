#ifndef PLAYER_CONTROLLER_H_
#define PLAYER_CONTROLLER_H_

#include <entity/ScriptBehavior.h>
#include <entity/Entity.h>

class PlayerController : public palmx::ScriptBehavior
{
public:
	void Update(palmx::EntityID entityID, float deltaTime) override;

private:
	float _movementSpeed = 3.5f;
	float _mouseSensitivity = 0.1f;
};

#endif