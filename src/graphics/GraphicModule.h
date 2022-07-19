#ifndef GRAPHIC_MODULE_H
#define GRAPHIC_MODULE_H
#ifdef _WIN32
#pragma once
#endif

#include "../IModule.h"
#include "gui_controls/Frame.h"
#include <Windows.h>
#include <vector>

class GraphicModule : public ISystem {
public:
	GraphicModule();
	~GraphicModule();
	
	// Inherited via ISystem
	virtual void Init() override;
	virtual void Update() override;
	virtual void Shutdown() override;
	virtual void OnEvent(C_ModuleEvent* i_CSystemEvent) override;

	static void AddElementToList(gui_controls::Panel* p_PanelToAdd);
	
	gui_controls::Panel* GetRoot() {
		return m_pROOT;
	}

	gui_controls::Panel* GetViewport() {
		return m_pViewport;
	}

private:
	HINSTANCE* m_phInstance = nullptr;

	gui_controls::Panel* m_pROOT = nullptr;
	gui_controls::Panel* m_pViewport = nullptr;

	static std::vector<gui_controls::Panel*> s_vecPanels;
};

#endif // GRAPHIC_MODULE_H