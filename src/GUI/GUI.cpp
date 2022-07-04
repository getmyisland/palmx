#include "GUI.h"

#include "../SystemHandler.fwd.h"
#include <iostream>

GUI::GUI() {};
GUI::~GUI() {};

void GUI::Init() {
	m_phInstance = SystemHandler::Instance().GetHInstance();

	Panel SavRootPanel = Panel(m_phInstance, nullptr, L"Palm Engine", CS_HREDRAW | CS_VREDRAW, WS_EX_APPWINDOW, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, 0, 0, 1280, 720);
	m_pRootPanel = &SavRootPanel;

	Panel SavBaseViewportPanel = Panel(m_phInstance, m_pRootPanel, L"BaseViewport", SavRootPanel.GetPosX(), SavRootPanel.GetPosY(), SavRootPanel.GetWidth(), SavRootPanel.GetHeight());
}

void GUI::Update() {

}

void GUI::Shutdown() {

}

void GUI::OnEvent(SystemEvent i_SysEvent) {

}

std::vector<Panel*> GUI::s_vecPanels = {};

void GUI::AddElementToList(Panel* panelToAdd)
{
	GUI::s_vecPanels.push_back(panelToAdd);

	std::wcout << "Added " << panelToAdd->GetWindowName() << " to the list" << std::endl;
}