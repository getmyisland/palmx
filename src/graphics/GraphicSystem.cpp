#include "GraphicSystem.h"
#include "../SystemManager.h"
#include <iostream>

GraphicSystem::GraphicSystem() {};
GraphicSystem::~GraphicSystem() {};

void GraphicSystem::Init() {
	m_phInstance = SystemManager::Instance().GetHInstance();

	gui_controls::Frame ROOT = gui_controls::Frame(m_phInstance, nullptr, L"PalmEngine");
	m_pROOT = &ROOT;

	gui_controls::Panel Viewport = gui_controls::Panel(m_phInstance, m_pROOT, L"BaseViewport", 0, 0, 1920, 1080);
	m_pViewport = &Viewport;
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