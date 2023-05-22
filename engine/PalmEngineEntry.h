#ifndef _PALM_ENGINE_ENTRY_H__
#define _PALM_ENGINE_ENTRY_H__

namespace PalmEngine
{
	class PalmEngineEntry
	{
	public:
		PalmEngineEntry() {}
		~PalmEngineEntry() {}

		// Pure virtual funtion this is the entry point for the game
		virtual void Entry() = 0;
	};
}

#endif