#include "GUI.h"

#include "../SystemHandler.fwd.h"
#include <iostream>

GUI::GUI() {};
GUI::~GUI() {};

void GUI::Init() {
	hInstance = SystemHandler::Instance().GetInstance();

	Panel rootPanel = Panel(hInstance, nullptr, L"Palm Engine", CS_HREDRAW | CS_VREDRAW, WS_EX_APPWINDOW, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, 0, 0, 1920, 1080);
	p_RootPanel = &rootPanel;

	Panel childPanel = Panel(hInstance, p_RootPanel, L"Child Panel");
}

void GUI::Update() {

}

void GUI::Shutdown() {

}

void GUI::OnEvent(SystemEvent sysEvent) {

}

std::vector<Panel*> GUI::allElements = {};

void GUI::AddElementToList(Panel* panelToAdd)
{
	GUI::allElements.push_back(panelToAdd);

	std::wcout << "Added " << panelToAdd->GetWindowName() << " to the list" << std::endl;
}