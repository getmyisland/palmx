#ifndef _PE_SCRIPT_HOOK_H__
#define _PE_SCRIPT_HOOK_H__

#include <vector>

#include "ScriptBehavior.h"

namespace PalmEngine
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
