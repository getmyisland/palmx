#ifndef PALMX_SCRIPT_HOOK_H_
#define PALMX_SCRIPT_HOOK_H_

#include "ScriptBehavior.h"

#include <algorithm>
#include <vector>

namespace palmx
{
	struct ScriptHook
	{
	public:
		std::vector<ScriptBehavior*> GetScriptBehavior()
		{
			return _scriptBehaviors;
		}

		void AddScriptBehavior(ScriptBehavior& scriptBehavior)
		{
			_scriptBehaviors.push_back(&scriptBehavior);
		}

		void RemoveScriptBehavior(ScriptBehavior& scriptBehavior)
		{
			// Find the iterator pointing to the element in the vector
			auto it = std::find_if(_scriptBehaviors.begin(), _scriptBehaviors.end(),
				[&scriptBehavior](ScriptBehavior* element) { return element == &scriptBehavior; });

			// If the element is found, remove it from the vector
			if (it != _scriptBehaviors.end())
			{
				_scriptBehaviors.erase(it);
			}
		}

	private:
		std::vector<ScriptBehavior*> _scriptBehaviors;
	};
}

#endif
