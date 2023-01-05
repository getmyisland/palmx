#include "GraphicModule.h"
#include "../ModuleManager.h"
#include "../logging/Logger.h"
#include "SwapChain.h"

GraphicModule::GraphicModule() {};
GraphicModule::~GraphicModule() {};

void GraphicModule::Init()
{
	m_phInstance = MODULE_MANAGER.GetEngineInstance();

	gui_controls::Frame ROOT = gui_controls::Frame(m_phInstance, nullptr, L"Palm Engine", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, 0, 0, 1280, 720);
	m_pRootPanel = &ROOT;

	gui_controls::Panel Viewport = gui_controls::Panel(m_phInstance, m_pRootPanel, L"Base Viewport");
	m_pBaseViewportPanel = &Viewport;

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	UINT cDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
	};

	UINT cFeatureLevel = ARRAYSIZE(featureLevels);
	ID3D11DeviceContext* d3d11DeviceContext;

	HRESULT result = 0;
	for (UINT driverTypeIndex = 0; driverTypeIndex < cDriverTypes;)
	{
		result = D3D11CreateDevice(NULL, driverTypes[driverTypeIndex], NULL, NULL, featureLevels, cFeatureLevel, D3D11_SDK_VERSION, &m_pDevice, &m_featureLevel, &d3d11DeviceContext);

		if (SUCCEEDED(result))
		{
			break;
		}

		++driverTypeIndex;
	}

	if (FAILED(result))
	{
		//return false;
	}

	m_pDeviceContext = new DeviceContext(d3d11DeviceContext);

	m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_pDgxiDevice);
	m_pDgxiDevice->GetParent(__uuidof(IDXGIAdapter),(void**) &m_pDgxiAdapter);
	m_pDgxiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_pDgxiFactory);

	m_pSwapChain = CreateSwapChain();
	m_pSwapChain->Init(m_pBaseViewportPanel);

	// return true;
}

void GraphicModule::Update()
{
	if (m_pRootPanel == nullptr || m_pRootPanel->GetHandle() == nullptr)
	{
		LOGGER.Log(Logger::Severity::Error, "Root Panel Window Handler is null");
		return;
	}

	m_pDeviceContext->ClearRenderTargetColor(m_pSwapChain, 1, 0, 1, 1);
	m_pSwapChain->Present(false);

	// Message handling needs to be done after rendering
	// Because if a window is destroyed it will release all resources and the render function will try to use these resources after

	bRet = GetMessage(&msg, *m_pRootPanel->GetHandle(), NULL, NULL);
	if (bRet != 0)
	{
		if (bRet == -1)
		{
			LOGGER.LogLastError(Logger::Severity::Error, GetLastError());
			MODULE_MANAGER.KillGameLoop();
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void GraphicModule::Shutdown()
{
	return;

	m_pSwapChain->Release();

	m_pDgxiFactory->Release();
	m_pDgxiAdapter->Release();
	m_pDgxiDevice->Release();

	m_pDeviceContext->Release();
	m_pDevice->Release();
}

void GraphicModule::OnEvent(ModuleEvent* i_CSystemEvent)
{

}

SwapChain* GraphicModule::CreateSwapChain()
{
	return new SwapChain();
}

std::vector<gui_controls::Panel*> GraphicModule::s_vecAllPanels = {};
void GraphicModule::AddElementToList(gui_controls::Panel* p_pPanelToAdd)
{
	GraphicModule::s_vecAllPanels.push_back(p_pPanelToAdd);

	LOGGER.LogW(Logger::Severity::Info, L"Added " + std::wstring(p_pPanelToAdd->GetWindowName()) + L" panel to the panel list");
}

void GraphicModule::SetViewport(const Rect& size)
{
	//glViewport
}
