#include "GUI.h"
#include "../SystemHandler.h"
#include <iostream>

GUI::GUI() {};
GUI::~GUI() {};

void GUI::Init() {
	p_hInstance = SystemHandler::Instance().GetInstance();

	Panel rootPanel = Panel(p_hInstance, L"Palm Engine");
	p_RootPanel = &rootPanel;

	Panel childPanel = Panel(p_hInstance, p_RootPanel, L"Child Panel");
}

void GUI::Update() {

}

void GUI::Shutdown() {

}

void GUI::OnEvent(SystemEvent sysEvent) {

}

void GUI::AddPanelToList(Panel* panelToAdd)
{
	allPanels.push_back(panelToAdd);
}