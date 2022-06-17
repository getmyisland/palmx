#include "AppSystem.h"
#include "../SystemManager.h"
#include <iostream>

void AppSystem::Init() {
	SystemManager::GetInstance().GetInputSystem().AddListener(this);
}

void AppSystem::Update() {

}

void AppSystem::OnKeyDown(int key) {
	std::cout << "Key Down called" << std::endl;
}

void AppSystem::OnKeyUp(int key) {

}
