#pragma once

#include "InputSystem.fwd.h"
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
	virtual void OnEvent(SystemEvent i_SysEvent) override;

private:
	InputMapper m_InputMapper;
	InputCollector m_InputCollector = InputCollector(&m_InputMapper);
};