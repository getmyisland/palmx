#ifndef INPUT_MODULE_H
#define INPUT_MODULE_H
#ifdef _WIN32
#pragma once
#endif

#include "../IModule.h"
#include "InputCollector.h"
#include "InputMapper.h"

class InputModule : public IModule
{
public:
	InputModule();
	~InputModule();

	// Inherited via ISystem
	virtual void Init() override;
	virtual void Update() override;
	virtual void Shutdown() override;
	virtual void OnEvent(ModuleEvent* i_CSystemEvent) override;

private:
	InputMapper m_InputMapper;
	InputCollector m_InputCollector = InputCollector(&m_InputMapper);
};

#endif // INPUT_MODULE_H