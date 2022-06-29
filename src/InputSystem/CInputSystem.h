#pragma once

#include <Windows.h>
#include "../ISubSystem.h"
#include "InputMapper.h"

class CInputSystem : public ISubsystem {
public:
	CInputSystem() {};
	~CInputSystem() {};

	virtual void Init();
	virtual void Update();
	virtual void Shutdown();
	virtual void OnEvent(SystemEvent sysEvent);

private:
	InputMapper inputMapper;
};