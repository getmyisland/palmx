#ifndef PALMX_INPUT_MODULE_H_
#define PALMX_INPUT_MODULE_H_

#include <GLFW/glfw3.h>

namespace palmx
{
	class InputModule
	{
	public:
		InputModule();
		~InputModule();
		
		void StartUp(GLFWwindow* mainWindow);
		void ShutDown();

		void CollectInput(GLFWwindow* window);
	};
}

#endif