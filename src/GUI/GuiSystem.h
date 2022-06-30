#pragma once

#include "../ISystem.h"
#include "Panel.h"
#include <Windows.h>

class GuiSystem : public ISystem {
public:
	GuiSystem();
	~GuiSystem();
	
	// Inherited via ISystem
	virtual void Init() override;
	virtual void Update() override;
	virtual void Shutdown() override;
	virtual void OnEvent(SystemEvent sysEvent) override;

private:
	HINSTANCE* p_hInstance = nullptr;
	const Panel* p_RootPanel = nullptr;
};