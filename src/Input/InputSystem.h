#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H
#ifdef _WIN32
#pragma once
#endif

#include "../ISystem.h"
#include "InputCollector.h"
#include "InputMapper.h"

class InputSystem : public ISystem {
public:
	InputSystem();
	~InputSystem();

	// Inherited via ISystem
	virtual void Init() override;
	virtual void Update() override;
	virtual void Shutdown() override;
	virtual void OnEvent(CSystemEvent i_CSystemEvent) override;

private:
	InputMapper m_InputMapper;
	InputCollector m_InputCollector = InputCollector(&m_InputMapper);
};

#endif // INPUT_SYSTEM_H