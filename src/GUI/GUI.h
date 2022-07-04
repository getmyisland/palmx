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
	virtual void OnEvent(SystemEvent i_SysEvent) override;

	static void AddElementToList(Panel* p_PanelToAdd);

private:
	HINSTANCE* m_phInstance = nullptr;

	Panel* m_pRootPanel = nullptr;

	static std::vector<Panel*> s_vecPanels;
};