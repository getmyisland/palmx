#ifndef GRAPHIC_MODULE_H
#define GRAPHIC_MODULE_H
#ifdef _WIN32
#pragma once
#endif

#include "../IModule.h"
#include "window/Frame.h"
#include <Windows.h>
#include <d3d11.h>
#include <vector>
#include "SwapChain.h"
#include "math/Rect.h"
#include "DeviceContext.h"

class SwapChain;
class DeviceContext;

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
	
	void AddElementToList(gui_controls::Panel* p_pPanelToAdd);
	void SetViewport(const Rect& size);

	gui_controls::Panel* GetRootPanel()	{ return m_pRootPanel; }
	gui_controls::Panel* GetViewportPanel() { return m_pBaseViewportPanel; }

private:
	HINSTANCE* m_phInstance = nullptr;

	MSG msg;
	BOOL bRet = NULL;

	gui_controls::Panel* m_pRootPanel = nullptr;
	gui_controls::Panel* m_pBaseViewportPanel = nullptr;

	static std::vector<gui_controls::Panel*> s_vecAllPanels;

	DeviceContext* m_pDeviceContext = nullptr;

	ID3D11Device* m_pDevice = nullptr;
	D3D_FEATURE_LEVEL m_featureLevel;

	IDXGIDevice* m_pDgxiDevice = nullptr;
	IDXGIAdapter* m_pDgxiAdapter = nullptr;
	IDXGIFactory* m_pDgxiFactory = nullptr;

	SwapChain* m_pSwapChain = nullptr;
	friend class SwapChain;
};

#endif // GRAPHIC_MODULE_H