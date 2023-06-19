#ifndef PALMX_SCRIPT_HOOK_H_
#define PALMX_SCRIPT_HOOK_H_

#include "ScriptBehavior.h"

#include <vector>

namespace palmx
{
    class ScriptHook
    {
    public:
        ScriptHook() {}
        ~ScriptHook() {}

        std::vector<ScriptBehavior*> GetScriptBehavior()
        {
            return _scriptBehaviors;
        }

        void AddScriptBehavior(ScriptBehavior& scriptBehavior)
        {
            _scriptBehaviors.push_back(&scriptBehavior);
        }

        void RemoveScriptBehavior() {}

    private:
        std::vector<ScriptBehavior*> _scriptBehaviors;
    };
}

#endif
