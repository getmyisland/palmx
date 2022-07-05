#ifndef GUI_SYSTEM_H
#define GUI_SYSTEM_H
#ifdef _WIN32
#pragma once
#endif

#include "../ISystem.h"
#include "gui_controls/Panel.h"
#include <Windows.h>
#include <vector>

class GuiSystem : public ISystem {
public:
	GuiSystem();
	~GuiSystem();
	
	// Inherited via ISystem
	virtual void Init() override;
	virtual void Update() override;
	virtual void Shutdown() override;
	virtual void OnEvent(CSystemEvent i_CSystemEvent) override;

	static void AddElementToList(Panel* p_PanelToAdd);

private:
	HINSTANCE* m_phInstance = nullptr;

	Panel* m_pRootPanel = nullptr;

	static std::vector<Panel*> s_vecPanels;
};

#endif // GUI_SYSTEM_H