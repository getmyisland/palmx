#include "GraphicModule.h"
#include "../ModuleManager.h"
#include <iostream>

GraphicModule::GraphicModule() {};
GraphicModule::~GraphicModule() {};

void GraphicModule::Init()
{
	m_phInstance = ModuleManager::Instance().GetHInstance();

	gui_controls::Frame ROOT = gui_controls::Frame(m_phInstance, nullptr, L"PalmEngine", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, 0, 0, 1280, 720);
	m_pROOT = &ROOT;

	gui_controls::Panel Viewport = gui_controls::Panel(m_phInstance, m_pROOT, L"BaseViewport");
	m_pViewport = &Viewport;
}

void GraphicModule::Update()
{
	bRet = GetMessage(&msg, *m_pROOT->GetHandle(), NULL, NULL);

	if (bRet == -1)
	{
		std::wcout << GetLastError() << L" Error occured in main game loop" << std::endl;
		ModuleManager::Instance().KillGameLoop();
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

void GraphicModule::OnEvent(C_ModuleEvent* i_CSystemEvent)
{

}

std::vector<gui_controls::Panel*> GraphicModule::s_vecPanels = {};

void GraphicModule::AddElementToList(gui_controls::Panel* panelToAdd)
{
	GraphicModule::s_vecPanels.push_back(panelToAdd);

	std::wcout << "Added " << panelToAdd->GetWindowName() << " to the list" << std::endl;
}