#ifndef _PE_INPUT_MANAGER_H__
#define _PE_INPUT_MANAGER_H__

#include <PalmEngineSingleton.h>

#include <GLFW/glfw3.h>

namespace PalmEngine
{
	class InputManager : public PalmEngineSingleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();
		
		static InputManager& GetSingleton(void);
		static InputManager* GetSingletonPtr(void);

		void StartUp(GLFWwindow* mainWindow);
		void ShutDown();

		void CollectInput(GLFWwindow* window);
	};
}

#endif