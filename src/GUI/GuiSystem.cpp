#include "GuiSystem.h"
#include "../SystemHandler.h"
#include <iostream>

GuiSystem::GuiSystem() {};
GuiSystem::~GuiSystem() {};

void GuiSystem::Init() {
	p_hInstance = SystemHandler::Instance().getInstance();

	Panel rootPanel = Panel(p_hInstance, nullptr, L"Palm Engine");
	p_RootPanel = &rootPanel;
}

void GuiSystem::Update() {

}

void GuiSystem::Shutdown() {

}

void GuiSystem::OnEvent(SystemEvent sysEvent) {

}