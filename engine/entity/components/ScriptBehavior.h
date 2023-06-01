#ifndef _PE_SCRIPT_BEHAVIOR_H__
#define _PE_SCRIPT_BEHAVIOR_H__

#include "Transform.h"

namespace PalmEngine
{
	class ScriptBehavior
	{
	public:
		virtual void Update(float deltaTime, Transform& transform) = 0;
	};
}

#endif