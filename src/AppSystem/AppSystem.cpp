#include "AppSystem.h"
#include "../InputSystem/InputSystem.h"
#include <iostream>

AppSystem& AppSystem::GetInstance() {
	static AppSystem instance;

	return instance;
}

void AppSystem::Init() {
	InputSystem::GetInstance().AddListener(this);
}

void AppSystem::Update() {

}

void AppSystem::OnKeyDown(int key) {
	std::cout << "Key Down called" << std::endl;
}

void AppSystem::OnKeyUp(int key) {

}
