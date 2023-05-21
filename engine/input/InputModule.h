#ifndef _PE_INPUT_MODULE_H__
#define _PE_INPUT_MODULE_H__

#include "../IModule.h"

#include <GLFW/glfw3.h>

namespace PalmEngine
{
	class InputModule : public IModule
	{
	public:
		InputModule();
		~InputModule();

		virtual void StartUp() override;
		virtual void ShutDown() override;

		void CollectInput(GLFWwindow* window);
	};
}

#endif