#ifndef _PE_INPUT_MANAGER_H__
#define _PE_INPUT_MANAGER_H__

#include <PalmEngineSingleton.h>
#include <PalmEngineManager.h>
#include <GLFW/glfw3.h>

namespace PalmEngine
{
	class InputManager : PalmEngineManager, public PalmEngineSingleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();
		
		static InputManager& GetSingleton(void);
		static InputManager* GetSingletonPtr(void);

		virtual void StartUp() override;
		virtual void ShutDown() override;

		void CollectInput(GLFWwindow* window);
	};
}

#endif