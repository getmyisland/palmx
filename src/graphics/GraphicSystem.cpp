#include "GraphicSystem.h"
#include "../SystemManager.h"
#include <iostream>

GraphicSystem::GraphicSystem() {};
GraphicSystem::~GraphicSystem() {};

void GraphicSystem::Init() {
	m_phInstance = SystemManager::Instance().GetHInstance();

	gui_controls::Frame ROOT = gui_controls::Frame(m_phInstance, nullptr, L"PalmEngine", 0, 0, 1280, 720);
	m_pROOT = &ROOT;

	//gui_controls::Frame Viewport = gui_controls::Frame(m_phInstance, m_pROOT, L"BaseViewport", ROOT.GetPosX(), ROOT.GetPosY(), ROOT.GetWidth(), ROOT.GetHeight());
	//m_pViewport = &Viewport;
}

void GraphicSystem::Update() {};

void GraphicSystem::Shutdown() {

}

void GraphicSystem::OnEvent(CSystemEvent i_CSystemEvent) {

}

std::vector<gui_controls::Panel*> GraphicSystem::s_vecPanels = {};

void GraphicSystem::AddElementToList(gui_controls::Panel* panelToAdd)
{
	GraphicSystem::s_vecPanels.push_back(panelToAdd);

	std::wcout << "Added " << panelToAdd->GetWindowName() << " to the list" << std::endl;
}