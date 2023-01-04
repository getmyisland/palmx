#ifndef GRAPHIC_MODULE_H
#define GRAPHIC_MODULE_H
#ifdef _WIN32
#pragma once
#endif

#include "../IModule.h"
#include "../window/Frame.h"
#include <Windows.h>
#include <d3d11.h>
#include <vector>
#include "SwapChain.h"

class SwapChain;

class GraphicModule : public IModule
{
public:
	GraphicModule();
	~GraphicModule();

	// Inherited via ISystem
	virtual void Init() override;
	virtual void Update() override;
	virtual void Shutdown() override;
	virtual void OnEvent(ModuleEvent* i_CSystemEvent) override;

	SwapChain* CreateSwapChain();

	static void AddElementToList(gui_controls::Panel* p_PanelToAdd);

	gui_controls::Panel* GetRoot()
	{
		return m_pROOT;
	}

	gui_controls::Panel* GetViewport()
	{
		return m_pViewport;
	}

private:
	HINSTANCE* m_phInstance = nullptr;

	MSG msg;
	BOOL bRet = NULL;

	gui_controls::Panel* m_pROOT = nullptr;
	gui_controls::Panel* m_pViewport = nullptr;

	static std::vector<gui_controls::Panel*> s_vecPanels;

	ID3D11Device* m_pDevice = nullptr;
	D3D_FEATURE_LEVEL m_featureLevel;
	ID3D11DeviceContext* m_pDeviceContext = nullptr;

	IDXGIDevice* m_pDgxiDevice = nullptr;
	IDXGIAdapter* m_pDgxiAdapter = nullptr;
	IDXGIFactory* m_pDgxiFactory = nullptr;

	SwapChain* m_pSwapChain = nullptr;
	friend class SwapChain;
};

#endif // GRAPHIC_MODULE_H