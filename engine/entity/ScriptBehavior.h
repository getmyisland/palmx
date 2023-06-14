#ifndef PALMX_BEHAVIOR_H_
#define PALMX_BEHAVIOR_H_

#include <entity/Entity.h>

namespace palmx
{
	class ScriptBehavior
	{
	public:
		// Gets called each frame
		virtual void Update(EntityID entityID, float deltaTime) = 0;
	};
}

#endif