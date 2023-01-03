#include "GraphicModule.h"
#include "../ModuleManager.h"
#include "../logging/Logger.h"

GraphicModule::GraphicModule() {};
GraphicModule::~GraphicModule() {};

void GraphicModule::Init()
{
	m_phInstance = MODULE_MANAGER.GetEngineInstance();

	gui_controls::Frame ROOT = gui_controls::Frame(m_phInstance, nullptr, L"Palm Engine", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, 0, 0, 1280, 720);
	m_pROOT = &ROOT;

	gui_controls::Panel Viewport = gui_controls::Panel(m_phInstance, m_pROOT, L"Base Viewport");
	m_pViewport = &Viewport;
}

void GraphicModule::Update()
{
	bRet = PeekMessage(&msg, *m_pROOT->GetHandle(), NULL, NULL, PM_REMOVE);
	if (bRet == -1)
	{
		LOGGER.Log(Logger::Severity::Error, GetLastError() + " error occured in update loop");
		MODULE_MANAGER.KillGameLoop();
	}
	else
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void GraphicModule::Shutdown()
{

}

void GraphicModule::OnEvent(ModuleEvent* i_CSystemEvent)
{

}

std::vector<gui_controls::Panel*> GraphicModule::s_vecPanels = {};

void GraphicModule::AddElementToList(gui_controls::Panel* panelToAdd)
{
	GraphicModule::s_vecPanels.push_back(panelToAdd);

	LOGGER.LogW(Logger::Severity::Info, L"Added " + std::wstring(panelToAdd->GetWindowName()) + L" panel to the panel list");
}