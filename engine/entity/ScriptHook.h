#ifndef PALMX_SCRIPT_HOOK_H_
#define PALMX_SCRIPT_HOOK_H_

#include <vector>

#include "ScriptBehavior.h"

namespace palmx
{
    class ScriptHook
    {
    public:
        ScriptHook() {}
        ~ScriptHook() {}

        std::vector<ScriptBehavior*> GetScriptBehavior()
        {
            return _scriptBehavior;
        }

        void AddScriptBehavior(ScriptBehavior& scriptBehavior)
        {
            _scriptBehavior.push_back(&scriptBehavior);
        }

        void RemoveScriptBehavior() {}

    private:
        std::vector<ScriptBehavior*> _scriptBehavior;
    };
}

#endif
