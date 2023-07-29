#ifndef PALMX_SCRIPT_HOOK_H
#define PALMX_SCRIPT_HOOK_H

#include "script_behavior.h"

#include <algorithm>
#include <vector>

namespace palmx
{
	struct ScriptHook
	{
	public:
		std::vector<ScriptBehavior*> GetScriptBehavior()
		{
			return script_behaviors_;
		}

		void AddScriptBehavior(ScriptBehavior& script_behavior)
		{
			script_behaviors_.push_back(&script_behavior);
		}

		void RemoveScriptBehavior(ScriptBehavior& script_behavior)
		{
			// Find the iterator pointing to the element in the vector
			auto it = std::find_if(script_behaviors_.begin(), script_behaviors_.end(),
				[&script_behavior](ScriptBehavior* element) { return element == &script_behavior; });

			// If the element is found, remove it from the vector
			if (it != script_behaviors_.end())
			{
				script_behaviors_.erase(it);
			}
		}

	private:
		std::vector<ScriptBehavior*> script_behaviors_;
	};
}

#endif
