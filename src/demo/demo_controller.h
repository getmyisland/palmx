#ifndef PALMX_DEMO_CONTROLLER_H
#define PALMX_DEMO_CONTROLLER_H

#include "../engine/entity.h"
#include "../engine/script_behavior.h"

class DemoController : public palmx::ScriptBehavior
{
public:
	void Update(palmx::EntityID entity_id, float delta_time) override;

private:
	float movement_speed_ = 3.5f;
	float mouse_sensitivity_ = 0.1f;
};

#endif