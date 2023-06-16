#ifndef PALMX_INPUT_MANAGER_H_
#define PALMX_INPUT_MANAGER_H_

#include <Singleton.h>

#include <GLFW/glfw3.h>

namespace palmx
{
	class InputManager : public Singleton<InputManager>
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