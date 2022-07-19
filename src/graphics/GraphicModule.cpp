#include "GraphicModule.h"
#include "../ModuleManager.h"
#include <iostream>

GraphicModule::GraphicModule() {};
GraphicModule::~GraphicModule() {};

void GraphicModule::Init() 
{
	m_phInstance = ModuleManager::Instance().GetHInstance();

	gui_controls::Frame ROOT = gui_controls::Frame(m_phInstance, nullptr, L"PalmEngine");
	m_pROOT = &ROOT;

	//gui_controls::Panel Viewport = gui_controls::Panel(m_phInstance, m_pROOT, L"BaseViewport", 0, 0, 1920, 1080);
	//m_pViewport = &Viewport;
}

void GraphicModule::Update() {};

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