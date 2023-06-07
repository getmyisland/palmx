#ifndef _PE_SCRIPT_BEHAVIOR_H__
#define _PE_SCRIPT_BEHAVIOR_H__

#include <scene/Entity.h>

namespace PalmEngine
{
	class ScriptBehavior
	{
	public:
		// Gets called each frame
		virtual void Update(EntityID entityID, float deltaTime) = 0;
	};
}

#endif