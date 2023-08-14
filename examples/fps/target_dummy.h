#ifndef PALMX_FPS_TARGET_DUMMY_H
#define PALMX_FPS_TARGET_DUMMY_H

#include <palmx/script_behavior.h>

class TargetDummy : public palmx::ScriptBehavior
{
public:
	virtual void Update(palmx::EntityID entity_id, float delta_time) override;
};

#endif