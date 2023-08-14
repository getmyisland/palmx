#ifndef PALMX_FPS_FPS_CONTROLLER_H
#define PALMX_FPS_FPS_CONTROLLER_H

#include <palmx/entity.h>
#include <palmx/script_behavior.h>

class FpsController : public palmx::ScriptBehavior
{
public:
	void Update(palmx::EntityID entity_id, float delta_time) override;

private:
	float movement_speed_ = 3.5f;
	float mouse_sensitivity_ = 0.1f;
};

#endif