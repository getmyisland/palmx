#ifndef _PE_INPUT_MANAGER_H__
#define _PE_INPUT_MANAGER_H__

#include <PalmEngineManager.h>
#include <GLFW/glfw3.h>

namespace PalmEngine
{
	class InputManager : public PalmEngineManager
	{
	public:
		InputManager();
		~InputManager();

		virtual void StartUp() override;
		virtual void ShutDown() override;

		void CollectInput(GLFWwindow* window);
	};
}

#endif