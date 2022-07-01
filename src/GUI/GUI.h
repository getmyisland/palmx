#pragma once

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

	void AddPanelToList(Panel* panelToAdd);

private:
	HINSTANCE* p_hInstance = nullptr;

	Panel* p_RootPanel = nullptr;

	std::vector<Panel*> allPanels;
};