#ifndef RENDER_MODULE_H
#define RENDER_MODULE_H

#include "../IModule.h"
#include "shaders/Shader.h"

#include <GLFW/glfw3.h>

class RenderModule : public IModule
{
public:
	RenderModule();
	~RenderModule();

	virtual void Init() override;
	virtual void Shutdown() override;

	void Render(GLFWwindow* pWindow);

private:
	Shader _shader;

	unsigned int _VAO = 0;
	unsigned int _VBO = 0;
};

#endif