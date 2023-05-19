#ifndef INPUT_MODULE_H
#define INPUT_MODULE_H

#include "../IModule.h"

#include <GLFW/glfw3.h>

class InputModule : public IModule
{
public:
	InputModule();
	~InputModule();

	virtual void Init() override;
	virtual void Shutdown() override;

	void CollectInput(GLFWwindow* pWindow);
};

#endif