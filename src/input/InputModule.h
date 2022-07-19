#ifndef INPUT_MODULE_H
#define INPUT_MODULE_H
#ifdef _WIN32
#pragma once
#endif

#include "../IModule.h"
#include "C_InputCollector.h"
#include "C_InputMapper.h"

class InputModule : public IModule
{
public:
	InputModule();
	~InputModule();

	// Inherited via ISystem
	virtual void Init() override;
	virtual void Update() override;
	virtual void Shutdown() override;
	virtual void OnEvent(C_ModuleEvent* i_CSystemEvent) override;

private:
	C_InputMapper m_InputMapper;
	C_InputCollector m_InputCollector = C_InputCollector(&m_InputMapper);
};

#endif // INPUT_MODULE_H