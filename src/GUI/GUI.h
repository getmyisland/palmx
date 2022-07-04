#pragma once

#include "GUI.fwd.h"
#include "../ISystem.h"
#include "Panel.h"
#include <Windows.h>
#include <vector>

class GUI : public ISystem {
public:
	GUI();
	~GUI();
	
	// Inherited via ISystem
	virtual void Init() override;
	virtual void Update() override;
	virtual void Shutdown() override;
	virtual void OnEvent(SystemEvent sysEvent) override;

	static void AddElementToList(Panel* panelToAdd);

private:
	HINSTANCE* hInstance = nullptr;

	Panel* p_RootPanel = nullptr;

	static std::vector<Panel*> allElements;
};