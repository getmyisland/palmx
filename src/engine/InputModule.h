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
		
		void Start(GLFWwindow* mainWindow);
		void Stop();

		void CollectInput(GLFWwindow* window);
	};
}

#endif