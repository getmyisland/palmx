#ifndef PALMX_INPUT_SYSTEM_H
#define PALMX_INPUT_SYSTEM_H

#include <GLFW/glfw3.h>

namespace palmx
{
	class InputSystem
	{
	public:
		InputSystem();
		~InputSystem();
		
		void Start(GLFWwindow* main_window);
		void Stop();

		void CollectInput(GLFWwindow* window);
	};
}

#endif