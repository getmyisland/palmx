#include "GuiSystem.h"
#include "../SystemHandler.h"
#include <iostream>

GuiSystem::GuiSystem() {};
GuiSystem::~GuiSystem() {};

void GuiSystem::Init() {
	m_phInstance = SystemHandler::Instance().GetHInstance();

	Panel TempRootPanel = Panel(m_phInstance, nullptr, L"pe_client", CS_HREDRAW | CS_VREDRAW, WS_EX_APPWINDOW, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, 0, 0, 1280, 720);
	m_pRootPanel = &TempRootPanel;

	Panel TempBaseViewportPanel = Panel(m_phInstance, m_pRootPanel, L"base_viewport", TempRootPanel.GetPosX(), TempRootPanel.GetPosY(), TempRootPanel.GetWidth(), TempRootPanel.GetHeight());
}

void GuiSystem::Update() {

}

void GuiSystem::Shutdown() {

}

void GuiSystem::OnEvent(CSystemEvent i_CSystemEvent) {

}

std::vector<Panel*> GuiSystem::s_vecPanels = {};

void GuiSystem::AddElementToList(Panel* panelToAdd)
{
	GuiSystem::s_vecPanels.push_back(panelToAdd);

	std::wcout << "Added " << panelToAdd->GetWindowName() << " to the list" << std::endl;
}