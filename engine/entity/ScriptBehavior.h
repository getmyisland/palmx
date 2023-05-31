#ifndef _PE_SCRIPT_BEHAVIOR_H__
#define _PE_SCRIPT_BEHAVIOR_H__

#include <logging/LogManager.h>

namespace PalmEngine
{
	class ScriptBehavior
	{
	public:
		virtual void Update() = 0;
	};
}

#endif