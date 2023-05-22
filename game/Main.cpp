#include <GLFW/glfw3.h>

#include <PalmEngineRoot.h>

int main()
{
	const unsigned int width = 800;
	const unsigned int height = 600;
	PalmEngine::PalmEngineRoot(width, height);

	return 0;
}