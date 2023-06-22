#ifndef PALMX_INPUT_SYSTEM_H_
#define PALMX_INPUT_SYSTEM_H_

#include <GLFW/glfw3.h>

namespace palmx
{
	class InputSystem
	{
	public:
		InputSystem();
		~InputSystem();
		
		void Start(GLFWwindow* mainWindow);
		void Stop();

		void CollectInput(GLFWwindow* window);
	};
}

#endif