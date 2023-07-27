#ifndef PALMX_DEMO_CONTROLLER_H
#define PALMX_DEMO_CONTROLLER_H

#include "../engine/entity.h"
#include "../engine/script_behavior.h"

class DemoController : public palmx::ScriptBehavior
{
public:
	void Update(palmx::EntityID entityId, float deltaTime) override;

private:
	float _movementSpeed = 3.5f;
	float _mouseSensitivity = 0.1f;
};

#endif