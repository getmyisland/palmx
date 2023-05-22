#include <GLFW/glfw3.h>

#include "Test.h"
#include <PalmEngineEntry.h>
#include <PalmEngineRoot.h>

int main()
{
	Test test;
	PalmEngine::PalmEngineConfig config(test, 800, 600);
	PalmEngine::PalmEngineRoot palmEngineRoot(config);

	return 0;
}