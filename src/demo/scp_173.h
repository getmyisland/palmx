#ifndef PALMX_DEMO_SCP_173_H
#define PALMX_DEMO_SCP_173_H

#include "../engine/ScriptBehavior.h"

class SCP_173 : public palmx::ScriptBehavior
{
public:
	virtual void Update(palmx::EntityID entityId, float deltaTime) override;
};

#endif