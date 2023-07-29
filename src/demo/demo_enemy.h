#ifndef PALMX_DEMO_ENEMY_H
#define PALMX_DEMO_ENEMY_H

#include "../engine/script_behavior.h"

class DemoEnemy : public palmx::ScriptBehavior
{
public:
	virtual void Update(palmx::EntityID entity_id, float delta_time) override;
};

#endif