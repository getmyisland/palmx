#ifndef PALMX_SCRIPT_BEHAVIOR_H
#define PALMX_SCRIPT_BEHAVIOR_H

#include "entity.h"

namespace palmx
{
	class ScriptBehavior
	{
	public:
		// Gets called each frame
		virtual void Update(EntityID entity_id, float delta_time) = 0;
	};
}

#endif